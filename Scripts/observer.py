#!/usr/bin/python3

import ipc_lwm2m_server as server
import ipc
import ipc_core
import re
import socket
import xml.etree.ElementTree as ET
import os


class ResponseException(Exception):
    pass

class EstablishNotify(ipc_core.IpcRequest):
    MessageType = "EstablishNotify"

class CarparkObserver():
    MAX_RECEIVE=65536
    def __init__(self, port, ipc_port):
        self.port = port
        self.ipc_port = ipc_port
        ipc = "127.0.0.1:" + str(ipc_port)

        self.socket = None
        self.address = None
        self._create_socket(ipc);

        response = self._send_request(server.ConnectRequest(), server.ConnectResponse)
        self._session_id = response.session_id
        print("Server started with {} id".format(self._session_id))

    def disconnect(self):
        request = server.DisconnectRequest(self._session_id)
        self._send_request(request)

    def list_clients(self):
        request = server.ListClientsRequest(self._session_id)
        response = self._send_request(request, server.ListClientsResponse)
        return response.getClientIDs()

    def observe(self, client_id):
        request = server.ObserveRequest(self._session_id)
        request.add((client_id, (1337, 0, 1)))
        response = self._send_request(request, server.ObserveResponse)
        request = EstablishNotify(session_id = self._session_id)
        response = self._send_request(request)
        print(response)

    def read_data(self, type=None):
        data = self.socket.recv(self.MAX_RECEIVE).decode("utf-8")
        try:
            if type is not None:
                return type(data)
        except:
            raise ResponseException(data)
        return data

    def _send_request(self, request, response_class=None):
        # send UDP packet
        self.socket.sendto(request.serialize(), (self.address, self.ipc_port))

        # retrieve and print response
        return self.read_data(response_class)

    def _create_socket(self, ipc_string):
        address, port = ipc_string.split(":")
        self.ipc_port = int(port)
        self.address = address
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

CACHE_PATH="/var/carpark"
observer = CarparkObserver(7100, 54321)

try:
    os.mkdir(CACHE_PATH)
except OSError as e:
    pass

cache_files = {}

for client in observer.list_clients():
    observer.observe(client)
    cache_files[client] = "{}/{}".format(CACHE_PATH, client)
    os.system("echo '1' > {}".format(cache_files[client]))
while True:
    data = observer.read_data()
    root = ET.fromstring(data)
    if root.tag != "Notification":
        print("Received non-notification")
        continue
    try:
        for client in root.findall(".//Client"):
            client_id = str(client.find("ID").text)
            value = int(client.find(".//Value").text)
            print("{} has now value {}".format(client_id, value))
            try:
                f = cache_files[client_id]
                os.system("echo '{}' > {}".format(value, f))
            except KeyError as key_e:
                print("Key error when writing")
    except Exception as e:
        print("Failed to traverse {} due to {}".format(ET.tostring(root), e))

observer.disconnect();

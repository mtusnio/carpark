#!/bin/sh

awa_bootstrapd -e lo -p 15683 -c bootstrap/localhost.bsc -l ./awa_bootstrap.log -d
awa_serverd -e lo -p 5683 -i 54321 -l ./awa_server.log -d
awa_clientd -i 12345 -p 6000 -b coap://127.0.0.1:15683 -e Carpark1 -l ./awa_client.log -d

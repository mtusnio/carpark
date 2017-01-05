# Carpark

## Introduction

A demo which uses the motion sensors to simulate a car park, while also using a local AwaLWM2M daemon & IPC to communicate with a nodejs application displaying the carpark's status.

###### Click the thumbnail to view video
[![Carpark video](http://img.youtube.com/vi/HeCg7sNAau4/0.jpg)](http://www.youtube.com/watch?v=HeCg7sNAau4 "Carpark demo")

## Requirements

Hardware:
- Ci40
- At least one 6lowpan clicker with a motion click

To download packages the Ci40 needs to have Internet access, however this is not required to run the webapp itself.

## Setup

After cloning the repo make sure to get the AwaLWM2M submodule.

```sh
git submodule update --init
```

### Ci40

A few packages need to be installed on the Ci40, run following commands:

```sh
opkg update
opkg install nodejs npm python3 python3-pip awalwm2m
pip install future
```

Now copy over the Scripts and Webapp folders onto your board, as well as copy ipc_core.py, ipc.py, ipc_lwm2m_server.py and ipc_lwm2m_client.py from Clicker/AwaLWM2M/api/python to the Scripts folder on the Ci40. First we will verify whether the Webapp runs properly. Navigate to the Webapp folder and run:

```sh
npm install
npm start
```

The bootup might take a while, after it is complete navigate your browser to http://\<ci40_ip\>:3000/carpark and check if you can see the carpark display. You can shut down the webapp for now.

#### Configuring AwaLWM2M

Next edit /etc/config/awalwm2m, it should in the end look like this:

```sh
BOOTSTRAP=coap://[fd77:9c74:ddee:c0e7::1]:15683
INTERFACE=lowpan0
ADDRESS_FAMILY=6
VERBOSE=--verbose
```

The IP in bootstrap should be either your link-local lowpan0 ip or global as you can find out here:

```sh
ifconfig lowpan0
```

Modify /etc/init.d/awa_bootstrapd by removing $FLOW_CONFIG from the start-stop-daemon call, and change LOCAL_CONFIG to /etc/lwm2m/localhost.bsc. Similarly to /etc/config/awalwm2m, your localhost.bsc file should look like this (replace ip as mentioned above):

```sh
ServerURI=coap://[fd77:9c74:ddee:c0e7::1]:5683
SecurityMode=0
PublicKey=[PublicKey]
SecretKey=[SecretKey]
ServerID=1
HoldOffTime=30
ShortServerID=1
Binding=U
LifeTime=30
DefaultMinimumPeriod=1
DefaultMaximumPeriod=-1
DisableTimeout=86400
NotificationStoringWhenDisabledOrOffline=true
```

Run /etc/init.d/awa_boostrapd restart for the changes to take effect.

### Clicker

Clone CreatorDev version of Contiki and LetMeCreateIot:

```sh
git clone -b creator https://github.com/Creatordev/contiki
git clone https://github.com/mtusnio/LetMeCreateIoT
```

Afterwards follow [installation instructions](https://github.com/mtusnio/LetMeCreateIoT#installation) for LMCIoT. Once that is done the only remaining change are the IPv6 defines for the Ci40. Edit project_conf.h and set BOOTSTRAP_IPv6_ADDR to your Ci40's link-local or global IP address. Finally run:

```sh
make CONTIKI=path/to/contiki
```

Finally flash the image onto the Clicker.

For extra clickers compile with:
```sh
make CONTIKI=path/to/contiki CLIENT_NAME=Carpark2
```

The app recognises clients starting with Carpark and can handle up to 10 of them.

## Running

Turn on the clicker, it should eventually connect to the Ci40 and register with AwaLWM2M server. Verify by running:

```sh
awa-server-list-clients
```

Navigate to the Scripts directory then run:

```sh
./server_defines.sh
./observer.py &
```

This will run the observer script in the background which updates the local cache of motion sensor states that is used by the webapp. Navigate to Webapp and run:

```sh
npm start
```

Once nodejs has managed to boot access http://\<ci40_ip\>:3000/carpark. Now every time the motion sensor toggles on a car should pop up on the display!

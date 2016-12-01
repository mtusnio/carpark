#!/bin/sh

awa-server-define -o 3306 -j "Actuation" -y "multiple" -r 5850 -n "On/Off" -t "boolean" -u "single" -q "mandatory" -k "rw"
awa-client-define -o 3306 -j "Actuation" -y "multiple" -r 5850 -n "On/Off" -t "boolean" -u "single" -q "mandatory" -k "rw"
awa-client-set --create /3306/0

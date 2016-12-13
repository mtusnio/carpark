#!/bin/sh

awa-client-define -o 1337 -j "CarDetector" -r 1 -n "Motion" -t "integer" -u "single" -q "optional" -k "r"
awa-client-set --create /1337/0
awa-client-set --create /1337/0/1
awa-client-set /1337/0/1=0

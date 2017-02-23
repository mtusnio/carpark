#!/bin/sh

awa-client-define -o 10241 -j "CarDetector" -r 1 -n "Motion" -t "integer" -u "single" -q "optional" -k "r"
awa-client-set --create /10241/0
awa-client-set --create /10241/0/1
awa-client-set /10241/0/1=0

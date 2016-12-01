#!/bin/sh

if [[ $# -ne 2 ]]; then
	echo "Params count"
	exit 1
fi

CLIENT_NAME=$1
OBJECT=$2

while true; do
	OUTPUT=$(awa-server-observe -n 1 -q -c $CLIENT_NAME $OBJECT | tail -n 1)
	echo "Got output: $OUTPUT"
	if [ "$OUTPUT" == "True" ]; then
		echo "Switching on"
		./relay_switch.py 1	
	else
		echo "Switching off"
		./relay_switch.py 0
	fi
done

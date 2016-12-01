#!/usr/bin/python3

import letmecreate.click.relay2 as relay
from letmecreate.core.common import MIKROBUS_1
import sys

value = int(sys.argv[1]);

if(value == 1):
    relay.enable_relay_1(MIKROBUS_1);
else:
    relay.disable_relay_1(MIKROBUS_1);

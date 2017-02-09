#!/bin/bash

cd tinydtls
for x in ../AwaLWM2M/lib/tinydtls/patches/*.patch; do
    patch < $x
done

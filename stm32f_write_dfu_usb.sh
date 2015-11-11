#!/bin/bash

if [ "$#" -ne 1 -o ! -f "$1" ]; then
    echo "Usage: $0 path/to/target.bin"
    exit 1
fi

sudo dfu-util -d 0483:df11 -c 1 -i 0 -a 0 -s 0x08000000 -D $1

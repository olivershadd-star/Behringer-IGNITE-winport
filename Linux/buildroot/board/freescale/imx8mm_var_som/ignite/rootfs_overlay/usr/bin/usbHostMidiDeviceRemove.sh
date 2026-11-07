#!/bin/sh

# Signal ignite to close the midi device input and output interfaces

pid=$(ps -e | grep Ignite | grep -v grep | awk '{print $1}')

if [ -n "$pid" ]; then
        kill -USR2 "$pid"
else
        echo "Ignite pid not found" > /dev/console
fi

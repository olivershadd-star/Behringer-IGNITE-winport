#!/bin/bash

VERSION_FILE="/etc/software_version"

if [[ -f "$VERSION_FILE" ]]; then
    DATE=$(grep "^DATE=" "$VERSION_FILE" | cut -d'=' -f2)

    if [[ -n "$DATE" ]]; then
        echo "Date from version file: $DATE"
        CURRENT_TIME=$(date +%T)
        DATE_TIME="${DATE} ${CURRENT_TIME}"

        date -s "$DATE_TIME"
        hwclock --systohc

        echo "RTC date set to: $DATE"
    else
        echo "Date not found in the version file."
    fi
else
    echo "File $VERSION_FILE does not exist."
fi

#!/bin/sh

echo "Starting Wifi service  ****************************"
rfkill unblock wifi
ip link set wlan0 up
wpa_supplicant -B -i wlan0 -c /usr/lib/firmware/mrvl/wpa_supplicant.conf
dhclient wlan0 &

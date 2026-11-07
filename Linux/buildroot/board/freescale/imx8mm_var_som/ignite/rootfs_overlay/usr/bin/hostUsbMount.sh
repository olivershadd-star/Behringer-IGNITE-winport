#!/bin/sh

if [  "$1"  -gt 0 ]; then
        fsck.vfat -y /dev/$21
        mount  /dev/$21 /mnt/flash
        echo "USB Device /dev/$21 MOUNTED"
else
        umount /mnt/flash
        echo "USB Device /dev/$21 UNMOUNTED"
fi

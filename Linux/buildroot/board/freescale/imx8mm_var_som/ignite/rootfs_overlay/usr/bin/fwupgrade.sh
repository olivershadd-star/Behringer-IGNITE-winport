#!/bin/sh

set -x
set -v

var=`/usr/sbin/fw_printenv | grep "mmcpart=" | sed s/.*=//`
echo ${var}
if [ $var = 1 ]
then
	echo "upgrading partiiton 2"
	upgrade=2
else
	echo "upgrading partition 1"
	upgrade=1
fi

upgrade_drive=/dev/mmcblk2p${upgrade}
current_drive=/dev/mmcblk2p${var}
echo ${drive}
/usr/bin/mkdir /mnt/sdcard
/usr/bin/mkdir /mnt/emmc
/usr/bin/mount /dev/mmcblk1p1 /mnt/sdcard

echo "formating the parition -> " ${upgrade_drive}

/usr/sbin/mkfs.ext4 -F ${upgrade_drive}
sleep 1
/usr/bin/mount ${upgrade_drive} /mnt/emmc
/usr/bin/tar xvf /mnt/sdcard/root/rootfs.tar -C /mnt/emmc
sleep 5
/usr/bin/umount /mnt/emmc
sleep 1
/usr/bin/umount /mnt/sdcard
sleep 1
/usr/sbin/fw_setenv mmcpart ${upgrade}
/usr/sbin/reboot -nf



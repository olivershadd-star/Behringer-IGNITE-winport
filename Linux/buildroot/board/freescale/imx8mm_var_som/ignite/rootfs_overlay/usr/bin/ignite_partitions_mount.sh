#!/bin/sh
myVariable=$(fw_printenv | grep emmc_boot= );
CURRENT_ROOT="${myVariable:10}"

# Get the kernel cmdline
cmdline=$(cat /proc/cmdline)

# Parse the kernel cmdline for mmblk
mmblk_device=$(echo $cmdline | grep -oE 'mmcblk[0-9]*')

# insert CV gate controle module
insmod /lib/modules/5.15.60-rt50/kernel/drivers/misc/cvctl.ko

echo $mmblk_device
echo $CURRENT_ROOT

	if [ $CURRENT_ROOT = 1 ]
	then
        echo "mounting APP partiiton 1"
		mount -o ro /dev/${mmblk_device}p6 /app
        upgrade=2
	else
		mount -o ro /dev/${mmblk_device}p3 /app
        echo "mounting APP partiiton 0"
        upgrade=1
	fi
	mkdir -p /home/ignite/Firmware_Update/


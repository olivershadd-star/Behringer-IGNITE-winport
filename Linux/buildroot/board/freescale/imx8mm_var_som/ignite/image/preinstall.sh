#!/bin/sh

if [ $# -lt 1 ]; then
	        exit 0;
fi
function get_current_root_device
{
for i in `cat /proc/cmdline`; do
		if [ ${i:0:5} = "root=" ]; then
			CURRENT_ROOT="${i:5}"
		fi
	done
}
function get_update_part
{
	CURRENT_PART="${CURRENT_ROOT: -1}"
	if [ $CURRENT_PART = "2" ]; then
		UPDATE_PART="5";
		KERNEL_PART="4";
		APP_PART="6";
		PARTITION="1";
	else
		UPDATE_PART="2";
		KERNEL_PART="1";
		APP_PART="3";
		PARTITION="0";
	fi
}
function get_update_device
{
	UPDATE_ROOT=${CURRENT_ROOT%?}${UPDATE_PART}
	UPDATE_KERNEL_ROOT=${CURRENT_ROOT%?}${KERNEL_PART}
	UPDATE_APP_ROOT=${CURRENT_ROOT%?}${APP_PART}
}
function format_update_device
{
	umount $UPDATE_ROOT
	umount $UPDATE_KERNEL_ROOT
	umount $UPDATE_APP_ROOT
	mkfs.ext4 $UPDATE_ROOT -F 
	mkfs.ext4 $UPDATE_KERNEL_ROOT -F
	mkfs.ext4 $UPDATE_APP_ROOT -F
}
if [ $1 == "preinst" ]; then
	# get the current root device
	get_current_root_device
	# get the device to be updated
	get_update_part
	get_update_device
	# format the device to be updated
	format_update_device
	# create a symlink for the update process
	ln -sf $UPDATE_ROOT /dev/update
	ln -sf $UPDATE_KERNEL_ROOT /dev/kernel
	ln -sf $UPDATE_APP_ROOT /dev/app
	touch /tmp/update_status
fi

if [ $1 == "postinst" ]; then
	get_current_root_device
	get_update_part
	/usr/bin/sync
	/usr/bin/sync
	echo 1 > /tmp/update_status
	fw_setenv emmc_boot $PARTITION
	sleep 1
	/usr/bin/sync
	/usr/bin/sync
fi



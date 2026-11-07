#!/bin/sh

factory_partition=/dev/mmcblk2p7
FACTORY_DIR=/mnt/factory

if [ ! -e $FACTORY_DIR ]; then
    mkdir $FACTORY_DIR
else 
    echo "$FACTORY_DIR already exists" 1>&2
fi

# mount parititon as readonly

/usr/bin/mount -o remount,ro $factory_partition   $FACTORY_DIR

#copy all files from /mnt/factory to respected locations.

#cp $FACTORY_DIR/project.files /home/Ignite/

#################################################################

echo "Restarting Services after factory reset"
#systemctl start ignite.service

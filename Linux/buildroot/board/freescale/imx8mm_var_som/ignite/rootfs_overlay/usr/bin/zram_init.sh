#!/bin/sh

# Number of ZRAM devices to configure
NUM_DEVICES=1

# Size of each ZRAM device (e.g., 512MB per device)
ZRAM_SIZE=512M

for i in $(seq 0 $((NUM_DEVICES - 1))); do
    # Create ZRAM device
    echo $ZRAM_SIZE > /sys/block/zram$i/disksize
    
    # Initialize ZRAM as swap
    mkswap /dev/zram$i
    swapon /dev/zram$i
done


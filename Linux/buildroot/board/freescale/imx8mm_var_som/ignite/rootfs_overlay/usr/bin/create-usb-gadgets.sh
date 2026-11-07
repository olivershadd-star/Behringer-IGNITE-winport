# cat /usr/bin/create-usb-gadgets.sh
#!/bin/sh
mkdir /sys/kernel/config/usb_gadget/gadgets
cd /sys/kernel/config/usb_gadget/gadgets
echo 0x1397 > idVendor
echo 0x12CC > idProduct
mkdir strings/0x409
echo 0000000000000000 > strings/0x409/serialnumber
echo "Ignite" > strings/0x409/product
mkdir configs/c.1
echo 250 > configs/c.1/MaxPower
echo 1 > os_desc/use
echo "MSFT100" > os_desc/qw_sign
echo 0x40 > os_desc/b_vendor_code
mkdir functions/ffs.utp0
mkdir /dev/usb-utp0
mount -t functionfs utp0 /dev/usb-utp0
ln -s functions/ffs.utp0 configs/c.1/
ln -s configs/c.1 os_desc

/bin/nohup /usr/bin/pcmode /dev/usb-utp0/ep0 &

echo run utp at /dev/usb-utp0/ep0;
while [ ! -e /dev/usb-utp0/ep1 ]
do
	echo "."
	sleep 1;
done

mkdir -p functions/midi.usb0 #Midi Gadget
mkdir -p functions/acm.GS0 #Serial gadget
mkdir functions/mass_storage.0 #Mass Storage gadget

echo "ignite_midi" > functions/midi.usb0/id
echo 6 > functions/midi.usb0/out_ports
echo 6 > functions/midi.usb0/in_ports
echo 1024 > functions/midi.usb0/buflen
echo 64 > functions/midi.usb0/qlen

ln -s functions/midi.usb0 configs/c.1/
ln -s functions/acm.GS0 configs/c.1/

echo /dev/mmcblk2p9 > functions/mass_storage.0/lun.0/file
ln -s functions/mass_storage.0 configs/c.1

echo "starting UDC"
ls /sys/class/udc > UDC

echo "USB Gadget MIDI, ACM, FFS & Mass Storage created"
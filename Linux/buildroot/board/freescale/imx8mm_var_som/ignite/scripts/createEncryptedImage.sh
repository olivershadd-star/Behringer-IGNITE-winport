#!/usr/bin/env bash

imx_image_size=$(stat -c%s output/images/Ignite.swu)
mcu_image_size=$(stat -c%s board/freescale/imx8mm_var_som/ignite/mcu-image/Ignite_MCU.hex)
version_size=$(stat -c%s board/freescale/imx8mm_var_som/ignite/version.txt)

get_image_size () {

	# Calculate the total size of images
	size=$(($imx_image_size + $mcu_image_size + $version_size))

	# convert size in MB
	size=$(echo "scale = 0; $size / 1048576" | bc)

	# Add ext4 fs headroom size of 15% of total size
	ext4_headroom=$(echo "scale = 0; $size * 30 / 100" | bc)
	size=`expr $size + $ext4_headroom`

	return $size
}

# Get the content of version.txt without leading/trailing whitespace
version=$(cat board/freescale/imx8mm_var_som/ignite/version.txt | grep 'Ignite' | awk '{print $1}')
version=$(echo "$version" | cut -d'_' -f4)
version_length=$(echo -n "$version" | wc -c)
echo $version_length
version=${version}E
dd if=/dev/null of=output/images/version_header bs=1 count=$version_length status=none
echo -n "$version" >output/images/version_header
echo $version

get_image_size
sudo dd if=/dev/zero of=output/images/Ignite.img bs=1M count=$?

imx_image_size=$(stat -c%s output/images/Ignite_fullimage.swu)
get_image_size
sudo dd if=/dev/zero of=output/images/Ignite_full.img bs=1M count=$?


# Format the .img file to ext4
sudo mkfs.ext4 output/images/Ignite.img -F
sudo mkfs.ext4 output/images/Ignite_full.img -F

# Create a directory to mount the .img file
mkdir -p ./tmp/ignite_image
mkdir -p ./tmp/ignite_full_image
 
# Mount the .img file to the directory
sudo mount -o loop output/images/Ignite.img ./tmp/ignite_image
sudo mount -o loop output/images/Ignite_full.img ./tmp/ignite_full_image

# Copy the .Hex and .swu files
sudo cp board/freescale/imx8mm_var_som/ignite/mcu-image/Ignite_MCU.hex ./tmp/ignite_image
sudo cp output/images/Ignite.swu ./tmp/ignite_image
sudo cp board/freescale/imx8mm_var_som/ignite/version.txt ./tmp/ignite_image
sudo cp board/freescale/imx8mm_var_som/ignite/mcu-image/Ignite_MCU.hex ./tmp/ignite_full_image
sudo cp output/images/Ignite_fullimage.swu ./tmp/ignite_full_image
sudo cp board/freescale/imx8mm_var_som/ignite/version.txt ./tmp/ignite_full_image

# Unmount the .img file
sudo umount ./tmp/ignite_image
sudo umount ./tmp/ignite_full_image

# Encrypt the image. The device decrypts it with the same key and openssl
# parameters (see decrptKey in FrontPannelManager.h).
FW_IMAGE_KEY="PJSDSOMIGNITEMTBE"
openssl enc -aes-256-cbc -pbkdf2 -salt -in output/images/Ignite.img -out output/images/Ignite_encrypted.img -k "$FW_IMAGE_KEY"
openssl enc -aes-256-cbc -pbkdf2 -salt -in output/images/Ignite_full.img -out output/images/Ignite_full_encrypted.img -k "$FW_IMAGE_KEY"
cat output/images/version_header output/images/Ignite_encrypted.img > output/images/Ignite_"$version".img
cat output/images/version_header output/images/Ignite_full_encrypted.img > output/images/Ignite_full_"$version".img

# cleanup temp files
sudo rm -f output/images/Ignite.img
sudo rm -rf ./tmp/ignite_image
sudo rm -f output/images/Ignite_full.img
sudo rm -rf ./tmp/ignite_full_image
sudo rm -f output/images/Ignite_encrypted.img
sudo rm -f output/images/Ignite_full_encrypted.img

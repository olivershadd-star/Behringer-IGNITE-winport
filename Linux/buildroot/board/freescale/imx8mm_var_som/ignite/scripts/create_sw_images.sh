#!/usr/bin/env bash

echo "Build Ignite Application software and create ext4 images"

#Clean old images and folders
rm -rf ./output/images/*.img ./output/images/tmp_mount

#clone Ignite Application source code and build
mkdir -p output/AppTemp
cd output/AppTemp
git clone "${IGNITE_SOURCE_GIT_URL:?Set IGNITE_SOURCE_GIT_URL to the IGNITE source repository}" Source
cd Source/Application
git checkout ui_dev
git pull
sudo cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=../../../../output/host/share/buildroot/toolchainfile.cmake -DCMAKE_INSTALL_PREFIX=./Build/  ./
sudo make -j32
if [ $? != 0 ]; then
   exit 1
fi

cd ../../../../
# Create file system images
sudo dd if=/dev/zero of=./output/images/ignite_apps.ext4 count=254800

# Convert to ext4 image
sudo mkfs.ext4 ./output/images/ignite_apps.ext4

# Copy application to app image
mkdir -p ./output/images/tmp_mount
sudo mount ./output/images/ignite_apps.ext4 ./output/images/tmp_mount
sudo cp -rf ./output/AppTemp/Source/Application/apps/ignite/Ignite_artefacts/Debug/* ./output/images/tmp_mount/
sudo umount ./output/images/tmp_mount

sync
sudo rm -rf ./output/images/tmp_mount
sudo gzip -f ./output/images/ignite_apps.ext4

 # copy MT SOM bootloader
sudo cp -f ./board/freescale/imx8mm_var_som/ignite/u-boot/imx-boot-imx8mm-ddr4-evk-sd.bin-flash_ddr4_evk ./output/images/

# Create Apps.tar package
cd ./output/AppTemp/Source/Application/apps/ignite/Ignite_artefacts/Debug
sudo tar cvfz appfs.tar.gz *
cd -

sudo mv ./output/AppTemp/Source/Application/apps/ignite/Ignite_artefacts/Debug/appfs.tar.gz ./output/images/

mkdir -p ./output/images/data
cd ./output/images/data
touch readme.txt
sudo tar cvfz ../data.tar.gz *
cd -
echo "Ignite Application software and image creation completed !!!"

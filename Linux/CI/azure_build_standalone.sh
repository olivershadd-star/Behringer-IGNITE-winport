set -x
sudo apt-get update
sudo apt install gcc g++ bash patch gzip bzip2 perl tar cpio unzip \
rsync file bc libasound2-dev libjack-jackd2-dev libcurl4-openssl-dev libfreetype6-dev \
libx11-dev libxcomposite-dev libxcursor-dev libxcursor-dev libxext-dev libxinerama-dev \
libxrandr-dev libxrender-dev libwebkit2gtk-4.0-dev libglu1-mesa-dev mesa-common-dev \
&& \
PATH=$(/usr/bin/printenv PATH | /usr/bin/perl -ne 'print join(":", grep { !/\/mnt\/[a-z]/ } split(/:/));') && \
cd buildroot && \

if [[ "$1" =~ "Ignite" ]]; then
        ./board/freescale/imx8mm_var_som/ignite/scripts/software_version.sh $2 $3 $4
fi

sudo chmod -R 0777 *
sudo make $1_defconfig && \
sudo make -j32 && \
sudo make sdk && \
cd - 
sudo mkdir buildroot/output/images/fw_files
sudo mkdir buildroot/output/images/fwUpgrade_files

sudo cp -f buildroot/output/images/*.dtb  buildroot/output/images/fw_files/
sudo cp -f buildroot/output/images/Image.gz  buildroot/output/images/fw_files/
sudo cp -f buildroot/output/images/imx8-boot-sd.bin  buildroot/output/images/fw_files/
if [[ "$1" =~ "Ignite" ]]; then
sudo cp -f buildroot/output/images/ignite_apps.ext4.gz  buildroot/output/images/fw_files/
sudo cp -f buildroot/output/images/*E.img  buildroot/output/images/fwUpgrade_files/
fi
if [ "$1" = "Kick" ]; then
sudo cp -f buildroot/output/images/Kick_apps.ext4.gz  buildroot/output/images/fw_files/
sudo cp -f buildroot/output/images/Kick_apps_debug.ext4.gz  buildroot/output/images/fw_files/
sudo cp -f buildroot/output/images/EKick*  buildroot/output/images/fw_files/
fi

sudo cp -f buildroot/output/images/sdcard_linux.img  buildroot/output/images/fw_files/
sudo cp -f buildroot/output/images/rootfs.ext4.gz  buildroot/output/images/fw_files/

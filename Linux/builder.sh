#!/bin/bash
set -x
sudo apt install gcc g++ bash patch gzip bzip2 perl tar cpio unzip \
rsync file bc libasound2-dev libjack-jackd2-dev libcurl4-openssl-dev libfreetype6-dev \
libx11-dev libxcomposite-dev libxcursor-dev libxcursor-dev libxext-dev libxinerama-dev \
libxrandr-dev libxrender-dev libwebkit2gtk-4.0-dev libglu1-mesa-dev mesa-common-dev \
&& \
PATH=$(/usr/bin/printenv PATH | /usr/bin/perl -ne 'print join(":", grep { !/\/mnt\/[a-z]/ } split(/:/));') && \
cd buildroot && \
rm -f ./package/psplash/*.patch
if [ "$1" = "Ignite" ]; then
	./board/freescale/imx8mm_var_som/ignite/scripts/software_version.sh false false true
fi
make $1_defconfig && \
make -j32

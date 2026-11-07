#!/usr/bin/env bash

set -x
CONTAINER_VER=""
PRODUCT_NAME="Ignite"
KERN_FILES="Image.gz imx8mm*"
cd board/freescale/imx8mm_var_som

cd -
cd  output/images/
tar cvfz kernel.tar.gz ${KERN_FILES}
cp ../../board/freescale/imx8mm_var_som/ignite/image/sw-description .
cp ../../board/freescale/imx8mm_var_som/ignite/image/preinstall.sh .

IMG_FILES="sw-description kernel.tar.gz rootfs.tar.gz appfs.tar.gz preinstall.sh"
for i in $IMG_FILES;do
                echo $i;done | cpio -ov -H crc >  ${PRODUCT_NAME}.swu

rm sw-description
rm preinstall.sh
cp ../../board/freescale/imx8mm_var_som/ignite/fullimage/sw-description .
cp ../../board/freescale/imx8mm_var_som/ignite/fullimage/preinstall.sh .

IMG_FILES="sw-description kernel.tar.gz rootfs.tar.gz  \
	appfs.tar.gz data.tar.gz preinstall.sh"
for i in $IMG_FILES;do
                echo $i;done | cpio -ov -H crc >  ${PRODUCT_NAME}_fullimage.swu

rm sw-description
rm preinstall.sh
rm -f kernel.tar.gz rootfs.tar.gz rootfs.tar

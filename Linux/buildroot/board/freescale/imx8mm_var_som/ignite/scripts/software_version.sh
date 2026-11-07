#!/bin/bash

echo "$PWD"
echo $PWD
echo "*******************************"

updateRev=$1
updateMajor=$2
updateMinor=$3

build_date=$(sed -n 's/^DATE=\(.*\)/\1/p'  < ./board/freescale/imx8mm_var_som/ignite/rootfs_overlay/etc/software_version)
imx_ver=$(sed -n 's/^IMX_VER=\(.*\)/\1/p'  < ./board/freescale/imx8mm_var_som/ignite/rootfs_overlay/etc/software_version)
ctl_ver=$(sed -n 's/^CTL_VER=\(.*\)/\1/p'  < ./board/freescale/imx8mm_var_som/ignite/rootfs_overlay/etc/software_version)

IFS="." read -ra parts <<<"$imx_ver"

rev=`echo $imx_ver | cut -d_ -f3`
rev=`echo $rev | cut -d. -f1`

if [[ $updateRev = "true" ]]; then
	((parts[0] =  $rev + 1))
fi

if [[ $updateMajor = "true" ]]; then
	((parts[1] = parts[1] + 1))
fi

if [[ $updateMinor = "true" ]]; then
	((parts[2] =  parts[2] + 1))
fi

if [[ $updateRev = "true" ]]; then
	NEXTVERSION="Ignite_SW_"$(IFS="."; echo "${parts[*]}")
else
	NEXTVERSION=$(IFS="."; echo "${parts[*]}")
fi

echo $newver

CURRENT_DATE=$(date +"%F")

#NEXTVERSION=$(echo ${imx_ver} | awk -F. -v OFS=. '{$NF += $2 ; print}')


echo "*******************************"
echo $NEXTVERSION
echo "*******************************"
echo $CURRENT_DATE
echo $new_imx_ver
echo $new_ctl_ver

sed -i "s/$build_date/$CURRENT_DATE/g" ./board/freescale/imx8mm_var_som/ignite/rootfs_overlay/etc/software_version
sed -i "s/$imx_ver/$NEXTVERSION/g" ./board/freescale/imx8mm_var_som/ignite/rootfs_overlay/etc/software_version
#sed -i "s/$ctl_ver/$new_ctl_ver/g" ./board/freescale/imx8mm_var_som/ignite/rootfs_overlay/etc/software_version

cp ./board/freescale/imx8mm_var_som/ignite/rootfs_overlay/etc/software_version ./board/freescale/imx8mm_var_som/ignite/version.txt

build_date=$(sed -n 's/^DATE=\(.*\)/\1/p'  < ./board/freescale/imx8mm_var_som/ignite/rootfs_overlay/etc/software_version)
imx_ver=$(sed -n 's/^IMX_VER=\(.*\)/\1/p'  < ./board/freescale/imx8mm_var_som/ignite/rootfs_overlay/etc/software_version)
ctl_ver=$(sed -n 's/^CTL_VER=\(.*\)/\1/p'  < ./board/freescale/imx8mm_var_som/ignite/rootfs_overlay/etc/software_version)

echo $build_date
echo $imx_ver
echo $ctl_ver

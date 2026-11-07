if [[ "$1" == "isMac" ]]
then
	echo "Build Ignite Software for Mac OS"
	cd ./Application
	cmake ./
	make -j16
	chmod +x apps/ignite/Ignite_artefacts/Ignite.app/Contents/MacOS/Ignite
	cd ../../
fi
if [[ "$1"  == "isLinux" ]]
then
	echo "Build Ignite Software for Linux"
	sudo bash ./Linux/CI/azure_build.sh Ignite

	if [ $? != 0 ]; then
		echo "Build failed"
		exit 1
	fi

	sudo mkdir Linux/buildroot/output/images/fw_files
	sudo mkdir Linux/buildroot/output/images/fwUpgrade_files

	sudo cp -f Linux/buildroot/output/images/*.dtb  Linux/buildroot/output/images/fw_files/
	sudo cp -f Linux/buildroot/output/images/Image.gz  Linux/buildroot/output/images/fw_files/
	sudo cp -f Linux/buildroot/output/images/imx8-boot-sd.bin  Linux/buildroot/output/images/fw_files/
	sudo cp -f Linux/buildroot/output/images/ignite_apps.ext4.gz  Linux/buildroot/output/images/fw_files/
	sudo cp -f Linux/buildroot/output/images/sdcard_linux.img  Linux/buildroot/output/images/fw_files/
	sudo cp -f Linux/buildroot/output/images/rootfs.ext4.gz  Linux/buildroot/output/images/fw_files/
	sudo cp -f Linux/buildroot/output/images/*E.img  Linux/buildroot/output/images/fwUpgrade_files/
fi
if [[ "$1"  == "isApp" ]]
then
	echo "Build Ignite Application for Linux"
	directory="./SDK"

	if [ ! -d "$directory" ]; then
		git clone --depth 1 --no-single-branch "${SDK_GIT_URL:?Set SDK_GIT_URL to the Buildroot SDK repository}" SDK --jobs 8
		cd ./SDK
		sudo git checkout Juce3.12
		sudo git pull
		sudo tar -xvzf aarch64-buildroot-linux-gnu_sdk-buildroot.tar.gz
		cd -
	fi
	cd ./Application
	sudo cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=../SDK/aarch64-buildroot-linux-gnu_sdk-buildroot/share/buildroot/toolchainfile.cmake -DCMAKE_INSTALL_PREFIX=./Build/  ./
	sudo make -j32

	if [ $? != 0 ]; then
		echo "Build failed"
		exit 1
	fi
	sudo cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=../SDK/aarch64-buildroot-linux-gnu_sdk-buildroot/share/buildroot/toolchainfile.cmake -DCMAKE_INSTALL_PREFIX=./Build/  ./
	sudo make -j32

	if [ $? != 0 ]; then
	echo "Build failed"
	exit 1
	fi
fi

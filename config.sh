#!/bin/bash
if "$( which apt-get )" 2> /dev/null; then
	echo "Debian-based distro detected."

	echo "Before you begin, make sure that you are connected to the internet."
	echo "This script is going to download and install some important packages: g++ nasm cmake libgmp3-dev libmpfr-dev libisl-dev libcloog-isl-dev libmpc-dev texinfo grub qemu genisoimage build-essential"
	echo "Press <enter> to continue"
	read

	packages=("g++" "nasm" "cmake" "libgmp3-dev" "libmpfr-dev" "libisl-dev" "libcloog-isl-dev" "libmpc-dev" "texinfo" "grub" "qemu" "genisoimage" "build-essential")

	for package in "${packages[@]}"
	do
		sudo apt-get install ${package}

		if [ $(dpkg-query -W ${package} 2>/dev/null | grep -c "ok installed") -eq 0 ];
		then
			echo "${package} - installed"
		else
			echo "Installation error: ${package} not found."
			exit
		fi
	done
else
	echo "Before you begin, make sure you have the follow packages installed"
	echo "01. gcc/g++"
	echo "02. nasm"
	echo "03. cmake"
	echo "04. grub"
	echo "05. GNU GMP"
	echo "06. GNU MPFR"
	echo "07. ISL"
	echo "08. ClooG"
	echo "09. GNU MPC"
	echo "10. GNU Texinfo"
	echo "11. qemu"
	echo "12. genisoimage"
	echo "13. build-essential"
	echo "For better compatibility, we recommend a debian-based distro: debian, ubuntu, lubuntu, xubuntu, kubuntu etc"
	echo "Press <enter> to continue"
	read
fi

export TARGET=i686-elf
export PREFIX="$HOME/.nk/cross"
export PATH="$PREFIX/bin:$PATH"

mkdir bin
mkdir bin/build-binutils
mkdir bin/build-gcc
mkdir bin/build-newlib

# Build binutils
cd bin/build-binutils
../../cross/binutils/configure --target=$TARGET --prefix=$PREFIX --disable-werror
make all
make install

# Build gcc bootstrap
cd ../build-gcc
../../cross/gcc/configure --target=$TARGET --prefix=$PREFIX --without-headers --with-newlib --with-gnu-as --with-gnu-ld --disable-werror
make all-gcc
make install-gcc

# Build newlib
cd ../build-newlib
../../cross/newlib/configure --target=$TARGET --prefix=$PREFIX --disable-werror
make all
make install

# Build GCC with newlib
cd ../build-gcc
../../cross/gcc/configure --target=$TARGET --prefix=$PREFIX --with-newlib --with-gnu-as --with-gnu-ld --disable-shared --disable-libssp --disable-werror
make all
make install

# Configuring environment variables
echo "PATH=$PATH" >> ~/.profile
echo "PATH=$PATH" >> ~/.bashrc

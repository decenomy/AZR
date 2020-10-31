#!/bin/bash
echo -e "\033[0;32mHow many CPU cores do you want to be used in compiling process? (Default is 1. Press enter for default.)\033[0m"
read -e CPU_CORES
if [ -z "$CPU_CORES" ]
then
	CPU_CORES=1
fi

# Clone Aezora code from the official Github repository
	git clone https://github.com/Aezora/Aezora.git

# Entering Aezora directory
	cd Aezora

# Compile dependencies
	cd depends
	make -j$(echo $CPU_CORES) HOST=x86_64-apple-darwin17 
	cd ..

# Compile Aezora
	./autogen.sh
	./configure --prefix=$(pwd)/depends/x86_64-apple-darwin17 --enable-cxx --enable-static --disable-shared --disable-debug --disable-tests --disable-bench
	make -j$(echo $CPU_CORES) HOST=x86_64-apple-darwin17
	make deploy
	cd ..

# Create zip file of binaries
	cp Aezora/src/aezorad Aezora/src/aezora-cli Aezora/src/aezora-tx Aezora/src/qt/aezora-qt Aezora/Aezora.dmg .
	zip Aezora-MacOS.zip aezorad aezora-cli aezora-tx aezora-qt Aezora.dmg
	rm -f aezorad aezora-cli aezora-tx aezora-qt Aezora.dmg

#! /bin/bash

make clean
make
./textfilewrite text.dat
./text2bin text.dat bin.dat
./binfileread bin.dat


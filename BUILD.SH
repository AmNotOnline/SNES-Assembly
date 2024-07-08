#!/bin/bash

# Build memory configs
wla-65816 -v -o ./TARGET/BANK00.O ./SRC/BANK00/HEADER.INC
wla-65816 -v -o ./TARGET/BANKXX.O ./SRC/BANK00/BANKHEADER.INC
wla-65816 -v -o ./TARGET/RAM_L.O  ./SRC/RAM/RAM_L.INC
wla-65816 -v -o ./TARGET/RAM_H.O  ./SRC/RAM/RAM_H.INC

# Link files
wlalink   -v -s -S -A LINKFILE    ./TARGET/TESTROM.SFC

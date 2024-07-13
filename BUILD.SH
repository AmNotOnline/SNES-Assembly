#!/bin/bash

# Build object
wla-65816 -v -o ./TARGET/OUT.O  ./SRC/HEADER.INC

# Link files
wlalink   -v -s -S -A LINKFILE  ./TARGET/TESTROM.SFC

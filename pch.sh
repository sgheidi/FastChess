#!/bin/sh
# generate a PCH file
g++ -Wall -fexceptions -g src/common/config.h src/common/util.h

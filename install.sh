#!/bin/sh

INC_DIR=/usr/include
LIB_DIR=/usr/lib

cp -v bin/libmlist.so "${LIB_DIR}"
cp -v src/m_list.h "${INC_DIR}"


#!/bin/sh

read  -p "INSTALL_DIR [/usr/bin]: " INSTALL_DIR

if [ -z "$INSTALL_DIR" ]
then
    INSTALL_DIR="/usr/bin"
fi

ln -s `pwd`/metil_comp/metil_comp $INSTALL_DIR


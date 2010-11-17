#!/bin/sh

read  -p "INSTALL_DIR [/usr/bin]: " INSTALL_DIR

if [ -z "$INSTALL_DIR" ]
then
    INSTALL_DIR="/usr/bin"
fi

set -o verbose #echo on
rm -f $INSTALL_DIR/metil_comp
ln -s `pwd`/metil_comp $INSTALL_DIR

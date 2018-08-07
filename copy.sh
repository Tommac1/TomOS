#!/bin/bash

EXT_1=1
EXT_2=1

while ((EXT_1 != 0 && EXT_2 != 0)) ; do
    cp ./src/config.txt /media/anon/boot/config.txt &> /dev/null
    EXT_1=$?
    cp ./kernel7.img /media/anon/boot/kernel7.img &> /dev/null
    EXT_2=$?
done

sync

echo "COPY FINISHED"


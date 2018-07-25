#!/bin/bash

FILE_1="dupa"
FILE_2="dupa2"

EXT_1=1
EXT_2=1

while ((EXT_1 != 0 && EXT_2 != 0)) ; do
    cp ./dupa ./asd/dupa &> /dev/null
    EXT_1=$?
    cp ./dupa ./asd/dupa2 &> /dev/null
    EXT_2=$?
done

sync

echo "COPY FINISHED"


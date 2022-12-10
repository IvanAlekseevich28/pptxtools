#!/bin/bash

TEXT=$(< $1)
#echo "$TEXT"

TARFILES=$(grep -r -L "Ascensio System SIA 2010" "$2")
#echo "$TARFILES"

for tarfile in $TARFILES
do
    echo $tarfile
    echo "$(echo "$TEXT"; cat "$tarfile")" > $tarfile
done

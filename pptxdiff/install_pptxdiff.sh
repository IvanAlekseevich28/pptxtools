#!/bin/bash

PROGNAME="pptxdiff"

if [ -z ["$(which meld)"] ]
then
	apt update
	apt install meld	
fi

if [ -z ["$(which unzip)"] ]
then
	apt update
	apt install unzip	
fi

if [ -z ["$(which xmllint)"] ]
then
	apt update
	apt install libxml2-utils	
fi

chmod +x $PROGNAME
cp $PROGNAME /usr/local/bin/${PROGNAME}

if [ -e /usr/local/bin/${PROGNAME} ]
then
	echo "${PROGNAME} installed!"
fi

#!/bin/bash

sudo apt install libxml2-utils emacs perl

chmod +x xmleditor
sudo cp xmleditor /usr/bin/XEd
sudo cp xmleditor.desktop /usr/share/application
sed -i '/application\/xml=/c\application\/xml=XEd.desktop/' ~/.config/mimeapps.list

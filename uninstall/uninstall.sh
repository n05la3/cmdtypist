#!/bin/bash
#remove cmdtypist and associated files.
sudo rm /usr/bin/cmdtypist &&
sudo rm -r $HOME/cmdtypist &&
echo "cmdtypist uninstalled" ||
echo "unable to install cmdtypist"; exit $?

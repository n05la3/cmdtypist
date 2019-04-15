#!/bin/bash
#remove cmdtypist and associated files.
sudo rm /usr/bin/cmdtypist &&
sudo rm -r $HOME/cmdTypist &&
echo "cmdtypist uninstalled" ||
echo "unable to uninstall cmdtypist"; exit $?

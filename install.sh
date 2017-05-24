#!/bin/bash
#Creates a symbolic link with begin to cmdtypist directory.
echo "Enter password to create a link for cmdtypist and access it from any directory" &&
sudo gcc cmdtypist.c -o cmdtypist &&
echo >> $HOME/.bashrc &&
echo "#symbolic link for cmdtypist">> $HOME/.bashrc &&
echo "alias begin='cd $HOME/cmdtypist/'">> $HOME/.bashrc &&
echo "alias cmdtypist='$HOME/cmdtypist/cmdtypist'">> $HOME/.bashrc &&
mkdir $HOME/cmtypist/
cp -r . $HOME/cmtypist/
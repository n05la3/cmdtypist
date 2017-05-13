#!home/.bashrc
#Creates a symbolic link with begin to cmdtypist directory.
echo "Enter password to create a link for cmdtypist and access it from any directory"
sudo echo >> $HOME/.bashrc&&
echo "#symbolic link for cmdtypist">> $HOME/.bashrc&&
echo "alias begin='cd $HOME/cmdtypistversion1.0/'">> $HOME/.bashrc&&
 
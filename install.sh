#!home/.bashrc
#Creates a symbolic link with begin to cmdtypist directory.
echo "Enter password to create a link for cmdtypist and access it from any directory";&&
gcc cmdtypist.c -o cmdtypist&&
sudo echo >> $HOME/.bashrc&&
echo "#symbolic link for cmdtypist">> $HOME/.bashrc&&
echo "alias begin='cd $HOME/cmdtypistversion1.0/'">> $HOME/.bashrc&&
echo "alias cmdtypist='$HOME/cmdtypistversion1.0/cmdtypist'">> $HOME/.bashrc&
cp -r ../cmdtypistversion1.0 $HOME/cmdtypistversion1.0/ 
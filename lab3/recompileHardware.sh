#!/bin/sh

#Recombile Verilog code
echo "#############################"
echo make quartus
make quartus
echo "#############################"

#Create rbf
echo "#############################"
echo make rbf
make rbf
echo "#############################"

#Git push
echo "#############################"
echo Upload to Github
git add *
git commit -m "compiled new version of hardware files"
git push

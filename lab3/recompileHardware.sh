#!/bin/sh

#Recombile Verilog code
echo "#############################"
echo make clean
make clean

echo make quartus
make quartus

#Create rbf
echo "#############################"
echo make rbf
make rbf

#Git push
echo "#############################"
echo Upload to Github
git add *
git commit -m "compiled new version of hardware files"
git push

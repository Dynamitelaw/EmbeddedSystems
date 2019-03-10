#!/bin/sh
set -x

#Recombile Verilog code
echo "#############################"
make clean
make quartus

#Create rbf
echo "#############################"
make rbf

#Git push
echo "#############################"
echo "Upload to Github"
git add *
git commit -m "compiled new version of hardware files"
git push

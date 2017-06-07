#!/bin/bash

echo verificando se Skullpi existe 
echo 
ls /home/pi | grep Skullpi | wc -l > /tmp/ver_skullpi.txt
cd /tmp
chmod 777 ver_skullpi.txt
echo ver_skullpi att
echo

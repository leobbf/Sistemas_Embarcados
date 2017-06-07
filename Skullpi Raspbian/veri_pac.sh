#!/bin/bash

echo verificando se pac.tar existe
echo 
ls /home/pi/Skullpi | grep pac.tar | wc -l > /tmp/ver_pac.txt
chmod 777 /tmp/ver_pac.txt
echo verificador att
echo

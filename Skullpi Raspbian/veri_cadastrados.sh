#!/bin/bash

echo verificando se cadastrados existe 
echo 
ls /home/pi | grep cadastrados.txt | wc -l > /tmp/ver_cadastrados.txt
cd /tmp
chmod 777 ver_cadastrados.txt
echo ver_cadastrados att
echo

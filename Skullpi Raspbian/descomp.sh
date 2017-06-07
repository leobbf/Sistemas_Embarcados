#!/bin/bash

echo Descompactar e excluir compactado pac.tar
cd /home/pi/Skullpi 
tar -zxvf pac.tar
rm pac.tar
cd /home/pi
chmod 777 -R Skullpi
echo arquivo pac.tar descompactado e excluido
echo

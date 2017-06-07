#!/bin/bash

echo compactar pasta Skullpi em pak.tar
cd /home/pi 
tar -zcf pak.tar Skullpi
mv pak.tar /tmp
echo arquivo pak.tar pronto para download
echo

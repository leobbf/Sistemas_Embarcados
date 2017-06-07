#!/bin/bash

echo verificando se existe um arquivo login.txt 
ls /tmp | grep login.txt | wc -l > /tmp/ver_login1.txt
chmod 777 /tmp/ver_login1.txt
echo ver_login att
echo

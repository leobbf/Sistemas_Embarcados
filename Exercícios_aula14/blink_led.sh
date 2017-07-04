#!/bin/bash

gpio_past=/sys/class/gpio
echo gpio4 OUT HIGH
echo 4 >> $gpio_past/export
sudo echo out > $gpio_past/gpio4/direction
sudo echo 1 > $gpio_past/gpio4/value
echo 5 segundos ligado
sleep 5
sudo echo 0 > $gpio_past/gpio4/value
echo 4 >> $gpio_past/unexport
echo FIM
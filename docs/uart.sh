#!/bin/bash

#set baud rate of the raspberry pi 4 model b GPIO pins 8 and 10 (GPIO 14 and GPIO 15) equal 
# to baud rate of the MAX-M10S GNSS module

#https://github.com/raspberrypi/documentation/blob/develop/documentation/asciidoc/computers/configuration/uart.adoc


#sudo apt-get install minicom
#sudo minicom -b 9600 -o -D /dev/serial0

#sudo apt-get install screen
#sudo screen /dev/serial0 9600

# /boot/cmdline.txt, remove console=serial0,115200. serial console can sometimes interfere with the UART
# /boot/firmware/config.txt, ensure the line enable_uart=1 is present

sudo stty -F /dev/serial0 9600

stty < /dev/serial0

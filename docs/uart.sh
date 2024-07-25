#!/bin/bash

#set baud rate of the raspberry pi 4 model b GPIO pins 8 and 10 (GPIO 14 and GPIO 15) equal 
# to baud rate of the MAX-M10S GNSS module

#https://github.com/raspberrypi/documentation/blob/develop/documentation/asciidoc/computers/configuration/uart.adoc

sudo stty -F /dev/serial0 9600

stty < /dev/serial0
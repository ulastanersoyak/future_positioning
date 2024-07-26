#!/usr/bin/env python

#import RPi.GPIO as GPIO
import serial

if __name__ == "__main__":
    ser = serial.Serial(
        port="/dev/serial0",
        baudrate=9600,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=1
    )
    if not ser.is_open:
        ser.open()
    ser.reset_input_buffer()
    bit_no = 0
    try:
        while(1):
            line = ser.readline().decode("utf-8").strip()
            if(line):
                print(f"bit{bit_no} := {line}")
                bit_no+=1
    except KeyboardInterrupt: 
        exit(0)
    except Exception as e:
        print("err := {e}") 
    finally:
        ser.close()

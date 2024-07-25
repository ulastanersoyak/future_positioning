#!/usr/bin/env python

#import RPi.GPIO as GPIO
import serial

if __name__ == "__main__":
    ser = serial.Serial(
        port='/dev/serial0',
        baudrate=9600,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        xonxoff=False,
        rtscts=False,
        dsrdtr=False
    )
    if not ser.is_open:
        ser.open()
    ser.reset_input_buffer()
    bit_no = 0
    try:
        bits = []
        while(1):
            bit = ser.read_all()
            bits.append(bit)
            if(len(bits) == 9):
                print(f"bit{bit_no} := {bits}")
                bits.clear()
                bit_no+=1
    except KeyboardInterrupt: 
        exit(0)
    except:
     print("err") 
    finally:
        ser.close()
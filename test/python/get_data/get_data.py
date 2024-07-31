#!/usr/bin/env python


import serial
import time


def get_serial(port: str, baudrate: int, parity_bit : serial, stop_bit: serial, byte_size: serial, timeout=1) -> serial.Serial:
    ser = serial.Serial(
        port=port,
        baudrate=baudrate,
        parity=parity_bit,
        stopbits=stop_bit,
        bytesize=byte_size,
        timeout=timeout
    )
    return ser

if __name__ == "__main__":
    ser = get_serial(port = "/dev/ttyAMA4", 
                     baudrate = 9600,
                     parity_bit = serial.PARITY_NONE, 
                     stop_bit = serial.STOPBITS_ONE, 
                     byte_size = serial.EIGHTBITS)
    if not ser.is_open:
        ser.open()
    ser.reset_input_buffer()
    line_no = 0
    time.sleep(1)
    try:
        while(1):
            line = ser.readline().decode("utf-8", errors="ignore").strip()
            if(line):
                print(f"message{line_no} := {line}")
                line_no+=1
    except KeyboardInterrupt: 
        exit(0)
    except Exception as e:
        print(f"err := {e}") 
    finally:
        ser.close()

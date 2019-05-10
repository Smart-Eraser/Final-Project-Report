from machine import UART
from machine import Pin
import utime
import socket

txpin = Pin(17, Pin.IN)
rxpin = Pin(16, Pin.OUT)

uart = UART(2 , 9600)

def UARTread():
  uart.init(9600, bits = 8, parity = 0, stop = 1, rx = 16, tx = 17)
  buff = bytearray(8)
  while not uart.any():
    pass
  uart.readinto(buff)
  uart.init(baudrate = 9600)
  return buff
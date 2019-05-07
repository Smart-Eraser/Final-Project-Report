from machine import Pin
from neopixel import NeoPixel
pin = Pin(5, Pin.OUT)
np = NeoPixel(pin, 32)
color = (10,0,0)
off = (0,0,0)
def lights(value):
  if value == 1:
    for i in range(0, 32):
     np[i] = color
    np.write()
    
  elif value == 0:
   for i in range(0,32):
      np[i] = off
  np.write()



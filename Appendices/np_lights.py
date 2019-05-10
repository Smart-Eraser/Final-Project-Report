from machine import Pin
from neopixel import NeoPixel
pin = Pin(5, Pin.OUT)
np = NeoPixel(pin, 32)
color1 = (0,10,0)
color2 = (10,0,0)
def lights(value):
  if value == 1:
    for i in range(0, 32):
     np[i] = color2
    np.write()
    
  elif value == 0:
   for i in range(0,32):
      np[i] = color1
  np.write()





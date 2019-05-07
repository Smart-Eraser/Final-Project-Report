from machine import Pin
import utime
import np_lights as f1
while True:
  trig=Pin(12,Pin.OUT)
  trig.off()
  utime.sleep_us(2)
  trig.on()
  utime.sleep_us(10)
  trig.off()
  echo=Pin(13,Pin.IN)
  while echo.value() == 0:
    pass
  t1 = utime.ticks_us()
  while echo.value() == 1:
    pass
  t2 = utime.ticks_us()
  cm = (t2-t1)/148.0
  utime.sleep_ms(1000)
  print(cm)
  if cm < 10:
    f1.lights(1)
  elif cm > 10:
    f1.lights(0)
  utime.sleep(0.1)





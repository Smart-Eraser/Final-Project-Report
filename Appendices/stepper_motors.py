#starting code from http://mpy-tut.zoic.org/tut/motors.html

import machine
import time

pins = [
    machine.Pin(12, machine.Pin.OUT),  # 1
    machine.Pin(13, machine.Pin.OUT),  # 2
    machine.Pin(14, machine.Pin.OUT),  # 4
    machine.Pin(15, machine.Pin.OUT),  # 8
]

phases = [ 10, 6, 5, 9 ]
x = -3.5;
number_of_rotations = x*1600 
x = 0;

if number_of_rotations < 0: #changes order of phases for CCW
  phases.reverse()
  number_of_rotations = number_of_rotations*-1
while x < number_of_rotations:
  for phase in phases:
    for n, p in enumerate(pins):
      pins[n](phase & 1<<n)
    time.sleep(0.0001)
    x = x + 1



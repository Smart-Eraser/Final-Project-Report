import socket
import sys
import _thread
import time
import utime
import struct
import network
import machine

pins = [
    machine.Pin(12, machine.Pin.OUT),  # 1
    machine.Pin(13, machine.Pin.OUT),  # 2
    machine.Pin(14, machine.Pin.OUT),  # 4
    machine.Pin(15, machine.Pin.OUT),  # 8
]
phases = [ 10, 6, 5, 9 ]

# ------------------------------------------------------------------
# Class Client that will be able to connect to a network, send user 
# inputted messages, and send ultrasonic and sound sensor readings  
# ----------------------------------------------------------------- 
class client:
  
  # ------------------------------------------------------------------
  # Initializations for variables to be used in the 'client' class
  # ----------------------------------------------------------------- 
  NW = ''                       # NW = NetWork
  
  # ------------------------------------------------------------------
  # host and port are used in creating a socket connection to a server,
  # Change according to the server you are tryin to connect to.
  # ---------------------------------------------------------------- 
  host = '192.168.4.1'        
  port = 80
  
  password = ''                 # Network password
  flag = 0                      # On/Off flag for sound sensor
  
  # ------------------------------------------------------------------
  # Function Name: wif_con
  # Description  : Enables the HUZZAH32 to connect to a specified
  #                network as a station.
  # ----------------------------------------------------------------- 
  def wifi(self):
    NW = 'SMERTERSER'
    password = 'faaaaaaaack'
    station = network.WLAN(network.STA_IF)
    station.active(True)
    try:
      station.connect(NW,password)
      print('Connected to ', NW)
    except KeyboardInterrupt:
      print('Connection Failed')
      sys.exit()
  # ------------------------------------------------------------------
  # Function Name: send_user
  # Description  : Takes user input and sends whatever the user types
  #                to a web server.
  # -----------------------------------------------------------------     
  def send(self):
    try:
      clisock = socket.socket( socket.AF_INET, socket.SOCK_STREAM )
    except:
      print('Failed to create socket')
      sys.exit()
    
    try:
        clisock.connect((self.host, self.port))
        print('Socket connected to ' + self.host + ' on port ' + str(self.port))
        print(self.receiveInit(clisock, 50000))
    except:
        print('Connection closed')
        sys.exit()
    k = 0
    instructions = [0,0,0,0]
    while(k<4):
      data = clisock.recv(1024)
      strings = str(data, 'utf8')
      #print(strings)
      if strings != '':
        num = int(strings)
        num = num*1600
        instructions[k] = num
        k = k + 1
        time.sleep(0.5)
      else:
        print(instructions)
        clisock.close()
        break
    x = 0
    z = 0
    for x in instructions:
      number_of_rotations = instructions[x]
      if number_of_rotations < 0: #changes order of phases for CCW
        phases.reverse()
        number_of_rotations = number_of_rotations*-1
      while z < number_of_rotations:
        for phase in phases:
          for n, p in enumerate(pins):
            pins[n](phase & 1<<n)
          time.sleep(0.0001)
          z = z + 1
    
    
# ------------------------------------------------------------------
  # Function Name: receive
  # Description  : handles any received data from a web server.
  # ------------------------------------------------------------------    
  def receiveInit(self, the_socket,timeout):
      
    #total data partwise in an array
    total_data=[]
    data = ''
      
    #beginning time
    begin = time.time()
    while 1:
      #if you got some data, then break after timeout
      if total_data and time.time() - begin > timeout:
        break
          
      #if you got no data at all, wait a little longer, twice the timeout
      elif time.time() - begin > timeout*2:
        pass
      #recv something
      try:
        data = the_socket.recv(1024)
        if data:
          total_data.append(data)
          #change the beginning time for measurement
          begin = time.time()
        else:
          #sleep for sometime to indicate a gap
          time.sleep(0.1)
      except:
        pass
       #join all parts to make final string
      return b''.join(total_data)
  
  # ------------------------------------------------------------------
  # Function Name: receive
  # Description  : handles any received data from a web server.
  # ------------------------------------------------------------------    
  def receiveLoop(self, the_socket,timeout, num):
      
    #total data partwise in an array
    total_data=[]
    data = ''
      
    #beginning time
    begin = time.time()
    while 1:
      #if you got some data, then break after timeout
      if total_data and time.time() - begin > timeout:
        break
          
      #if you got no data at all, wait a little longer, twice the timeout
      elif time.time() - begin > timeout*2:
        pass
      #recv something
      try:
        data = the_socket.recv(1024)
        strings = str(data, 'utf8')
        num = int(strings)
        num = num*1600
      except:
        pass
       #join all parts to make final string
      return num

client = client()








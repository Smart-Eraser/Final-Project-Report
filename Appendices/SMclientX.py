import socket
import sys
import _thread
import time
import utime
import struct
import network
import machine


# ------------------------------------------------------------------
# Class Client that will be able to connect to a network, send user 
# inputted messages, and send ultrasonic and sound sensor readings  
# ----------------------------------------------------------------- 
class client:
  AllBounds = []
  # ------------------------------------------------------------------
  # Initializations for variables to be used in the 'client' class
  # ----------------------------------------------------------------- 
  NW = ''                       # NW = NetWork
  
  # ------------------------------------------------------------------
  # host and port are used in creating a socket connection to a server,
  # Change according to the server you are tryin to connect to.
  # ---------------------------------------------------------------- 
  host = '192.168.1.100'        
  port = 8888
  
  password = ''                 # Network password
  flag = 0                      # On/Off flag for sound sensor
  
  # ------------------------------------------------------------------
  # Function Name: wif_con
  # Description  : Enables the HUZZAH32 to connect to a specified
  #                network as a station.
  # ----------------------------------------------------------------- 
  def wifi(self):
    NW = 'esp32-network'
    password = 'esp32esp32'
    station = network.WLAN(network.STA_IF)
    station.active(True)
    try:
      station.connect(NW,password)
    except KeyboardInterrupt:
      print('Connection Failed')
      sys.exit()
      
  # ------------------------------------------------------------------
  # Function Name: send_US
  # Description  : Sends readings from the ultrasonic sensor to a
  #                web server.
  # ----------------------------------------------------------------- 
  def SerpentineInit(self):
    def serpentine(top, left, bottom, right, delayx, delayy):
      def steppermotors(TopBound):
        pins = [
          machine.Pin(12, machine.Pin.OUT),  # 1
          machine.Pin(13, machine.Pin.OUT),  # 2
          machine.Pin(14, machine.Pin.OUT),  # 4
          machine.Pin(15, machine.Pin.OUT),  # 8
        ]

        phases = [ 10, 6, 5, 9 ]
        y = TopBound;
        number_of_rotations = y*57
        y = 0;

        if number_of_rotations < 0: #changes order of phases for CCW
          phases.reverse()
          number_of_rotations = number_of_rotations*-1
        while y < number_of_rotations:
          for phase in phases:
            for n, p in enumerate(pins):
              pins[n](phase & 1<<n)
            time.sleep(0.0001)
            y = y + 1
      
      Xdelay = delayx
      Ydelay = delayy
      LeftBound = left
      X_rotations = right - left
      TopBound = top
      Y_rotations = bottom - top
      
      setDelayX = Xdelay*(Y_rotations/240)
      setDelayY = Ydelay*(X_rotations/320)
      
      print('Starting position X = ', LeftBound)
      steppermotors(LeftBound)
      
      print('Starting position Y = ', TopBound)
      time.sleep(setDelayX)

      print('Number of rotations for X = ', X_rotations)
      print('Number of rotations for Y = ', Y_rotations)
      
      print('X starts by rotating: ', X_rotations)
      steppermotors(X_rotations)
      
      Numb_of_Y_pix_Rot = 20
      y_pos = 0

      while Y_rotations > 0:
        print('Y should rotate ', Y_rotations)
        time.sleep(setDelayX)
        Y_rotations = Y_rotations - Numb_of_Y_pix_Rot
        y_pos = Y_rotations
        X_rotations = -X_rotations
        LeftBound = X_rotations
        print('X should rotate ', X_rotations)
        steppermotors(X_rotations)
      if X_rotations < 0:
        X_rotations = -left
        print('X stopped at the bottom left corner, so it will rotate: ', -left)
        steppermotors(X_rotations)
        y_pos = y_pos*-1
        Y_rotations = -(bottom + y_pos)
        print(' and Y will rotate', -bottom)
        time.sleep(setDelayX)
      else: #X_rotations > 0
        X_rotations = -right
        print('X stopped at the bottom right corner, so it will rotate: ', -right)
        steppermotors(X_rotations)
        y_pos = y_pos*-1
        Y_rotations = -(bottom + y_pos) 
        print(' and Y will rotate', -bottom)
        time.sleep(setDelayX)
      
      time.sleep(setDelayY)
      time.sleep(setDelayX)
    
    instr1 = self.AllBounds[0]
    self.top1 = (instr1[0] << 8) + instr1[1] 
    self.left1 = (instr1[2] << 8) + instr1[3]
    self.bottom1 = (instr1[4] << 8) + instr1[5]
    self.right1 = (instr1[6] << 8) + instr1[7]
    
    print('top1 = ',self.top1) 
    print('left1 = ',self.left1)
    print('bottom1 = ',self.bottom1)
    print('right1 = ',self.right1)
    
    time.sleep(2)
    
    instr2 = self.AllBounds[1]
    self.top2 = (instr2[0] << 8) + instr2[1] 
    self.left2 = (instr2[2] << 8) + instr2[3]
    self.bottom2 = (instr2[4] << 8) + instr2[5]
    self.right2 = (instr2[6] << 8) + instr2[7]
    self.top2 = self.top2 + 80
    self.bottom2 = self.bottom2 + 80
    
    print('top2 = ',self.top2) 
    print('left2 = ',self.left2)
    print('bottom2 = ',self.bottom2)
    print('right2 = ',self.right2)
    
    time.sleep(1)
    
    instr3 = self.AllBounds[2]
    self.top3 = (instr3[0] << 8) + instr3[1] 
    self.left3 = (instr3[2] << 8) + instr3[3]
    self.bottom3 = (instr3[4] << 8) + instr3[5]
    self.right3 = (instr3[6] << 8) + instr3[7]
    self.top3 = self.top3 + 160
    self.bottom3 = self.bottom3 + 160
   
    print('top3 = ',self.top3) 
    print('left3 = ',self.left3)
    print('bottom3 = ',self.bottom3)
    print('right3 = ',self.right3)
    
    time.sleep(3)
    
    serpentine(self.top1, self.left1, self.bottom1, self.right1, 1, 4)
    print('check1')
    serpentine(self.top2, self.left2, self.bottom2, self.right2, 1, 4)
    print('check2')
    serpentine(self.top3, self.left3, self.bottom3, self.right3, 1, 4)
    return
     
  # ------------------------------------------------------------------
  # Function Name: send_user
  # Description  : Takes user input and sends whatever the user types
  #                to a web server.
  # -----------------------------------------------------------------     
  def WaitForInstructions(self):
    try:
      clisock = socket.socket( socket.AF_INET, socket.SOCK_STREAM )
    except:
      print('Failed to create socket')
      sys.exit()
    
    try:
        clisock.connect((self.host, self.port))
        print('Socket connected to ' + self.host + ' on port ' + str(self.port))
        print(self.receive(clisock, 5).decode())
    except:
        print(self.receive(clisock, 5).decode())
        print('Connection closed')
        sys.exit()
    inst = 0  
    self.AllBounds = []
    while(inst < 3):
      data = clisock.recv(4096)
      Bounds = list(data)
      self.AllBounds.append(Bounds)
      inst = inst + 1
      
    clisock.close()
    return
        
      #clieprint(self.receive(clisock, 5).decode())
  
  # ------------------------------------------------------------------
  # Function Name: receive
  # Description  : handles any received data from a web server.
  # ------------------------------------------------------------------    
  def receive(self, the_socket,timeout):
      
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

client = client()

client.wifi()

time.sleep(7)

while (True):

  client.WaitForInstructions()

  time.sleep(5)

  client.SerpentineInit()















import socket
import sys
import time
import network
import network
import socket
from UART import *
from _thread import *

class server:
  List1 = []
  List2 = []
  List3 = []
  NW = 'esp32-network'
  password = 'esp32esp32'
  def start(self):
    station = network.WLAN(network.STA_IF)
    station.active(True)
    try:
      station.connect(self.NW,self.password)
    except KeyboardInterrupt:
      print('Connection Failed')
      sys.exit()
    
    time.sleep(10)
    station_info = station.ifconfig()
    HOST = station_info[0]
    PORT = 8888	# Arbitrary non-privileged port
    
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    #Bind socket to local host and port
    try:
      s.bind((HOST, PORT))
    except:
      print('Bind failed')
      sys.exit()

    print('Socket created at ' + str(HOST) + ' with port ' + str(PORT) )	
    print('Socket bind complete')

    #Start listening on socket
    s.listen(10)
    print('Socket now listening')

    #Function for handling connections. This will be used to create threads
    def clientthread(conn, addr):
      #Sending message to connected client
        message = 'Welcome to the server.'
        conn.sendall(message.encode())
        mes = [b'ACK: ']
        data = ''
      #infinite loop so that function do not terminate and thread do not end.
        lock = _thread.allocate_lock()
      
        while self.List1 == []:
          pass  
        while not lock.acquire():
          pass
        print(self.List1)  
        #Send first set of instructions
        conn.sendall(self.List1)
        time.sleep(2)
        lock.release()
        
        while self.List2 == []:
          pass
        while not lock.acquire():
          pass
        print(self.List2)
        #Send second set of instructions
        conn.sendall(self.List2)
        time.sleep(2)
        lock.release()
        
        while self.List3 == []:
          pass
        while not lock.acquire():
          pass
        print(self.List3)
        #Send third set of instructions
        conn.sendall(self.List3)
        time.sleep(2)
        lock.release()
        
        conn.close()
        return
      
    #now keep talking with the client
    while 1:
      k = 0
      
        #wait to accept a connection - blocking call
      while (k < 2):
        conn, addr = s.accept()
        print('Connected with ' + str(addr[0]) + ' : ' + str(addr[1]))
        
        #start new thread takes 1st argument as a function name to be run, second is the tuple of arguments to the function.
        start_new_thread(clientthread ,(conn, addr))
        k = k + 1
      
      self.List1 = []
      self.List2 = []
      self.List3 = []
      self.List1 = UARTread()
      self.List2 = UARTread()
      self.List3 = UARTread()
      time.sleep(5)
      self.List1 = []
      self.List2 = []
      self.List3 = []
      
      k = 0

    s.close()
    
server = server()















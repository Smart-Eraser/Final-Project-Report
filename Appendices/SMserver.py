'''
	Simple socket server using threads
'''
import socket
import sys
from _thread import *
import time
import network

class server:
  
  NW = 'esp32-network'
  password = 'esp32esp32'
  def start(self):
    NW = input("Enter Wifi Name: ")
    password = input("Enter password: ")
    station = network.WLAN(network.STA_IF)
    station.active(True)
    try:
      station.connect(NW,password)
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
        conn.settimeout(60.0)
      #infinite loop so that function do not terminate and thread do not end.
        while True:
            try:
          #Receiving from client
                data = conn.recv(1024)
                mes.append(data)
                reply = b''.join(mes)

                if not data: 
                  break
                print('User ' + addr[0] + ' sent ' + data.decode())
                conn.send(reply)
                mes = [b'ACK: ']
            except Exception as e:
                print('Thread Closed ', e)
                conn.close()

      #came out of loop
        conn.close()
        print('Thread Closed')
      
    #now keep talking with the client
    while 1:
        #wait to accept a connection - blocking call
      conn, addr = s.accept()
      print('Connected with ' + str(addr[0]) + ' : ' + str(addr[1]))
      
      #start new thread takes 1st argument as a function name to be run, second is the tuple of arguments to the function.
      start_new_thread(clientthread ,(conn, addr))

    s.close()
server = server()

from socket import *
import time

address = ( '192.168.178.177', 5000) #Defind who you are talking to (must match arduino IP and port)
client_socket = socket(AF_INET, SOCK_DGRAM) #Set Up the Socket
client_socket.settimeout(1) #only wait 1 second for a response
#while(1): #Main Loop
#Attemp for without LOOOOOOOOOOOP
data = "on" #Set data forward backward was requested for stepper motor
data2 = data.encode("ascii") #data convert to object like byt
client_socket.sendto(data2, address) #send command to arduino
try:
    rec_data, addr = client_socket.recvfrom(2048) #Read response from arduino
    print(rec_data) #Print the response from Arduino
except:
    pass
time.sleep(2) #delay before sending next command

data = "back" #Set data switch backward was requested for stepper motor
data2 = data.encode("ascii") #data convert to object like byt
client_socket.sendto(data2, address) #send command to arduino
try:
    rec_data, addr = client_socket.recvfrom(2048) #Read response from arduino
    print(rec_data) #Print the response from Arduino
except:
    pass

time.sleep(5) #delay before sending next command

data = "on" #Set data switch backward was requested for stepper motor
data2 = data.encode("ascii") #data convert to object like byt
client_socket.sendto(data2, address) #send command to arduino
try:
    rec_data, addr = client_socket.recvfrom(2048) #Read response from arduino
    print(rec_data) #Print the response from Arduino
except:
    pass

time.sleep(5) #delay before sending next command

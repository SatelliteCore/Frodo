import socket
from datetime import datetime 
s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
#to find ip address on computer (server), type "ipconfig" into CMD,
#look at "Ethernet adapter Ethernet:" and find
#"Autoconfiguration IPv4 Address:" and enter the ip address
hostIP="169.254.95.36" 
#port number can be anything as long as it isnt already
#allocated by computer for different proccess
port=12345
s.bind((hostIP,port)) 
s.listen(1)
conn,addr=s.accept()
print("Connected by: "+str(addr)) #not required
file=open("Test.png","wb") #creates new file for writing binary data
data=conn.recv(1024)
print(datetime.now()) #prints start time (not required)
while data:
    file.write(data)
    data=conn.recv(1024)

    """ """
    #takes longer to finish running, but prints binary data being recieved from the Arduino
    #useful for debugging
    #print(data) #(not required)
    """ """
    
    #if statement just saves the file once client sends "Done"
    #"Done" will be sent from client once entire file is sent
    if len(data)==4 and data[0]==68 and data[1]==111 and data[2]==110 and data[3]==101:
        break
print(datetime.now()) #prints finish time (not required)
file.close() #closes and saves file
conn.close() #closes connection

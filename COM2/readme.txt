The two files, "host.py" and "client.ino" are both required to make this work

Running "host.py" (as long as hostIP address and port number both work), then "client.ino" (again, hostIP address, port number, and server address all need to work for machine), will cause a connected Arduino with Ethernet shiled to send the binary data of an image to machine running the python code, and the python code will create, write, and save all the binary data into the specified file format. 

Any print() or Serial.println() functions in either "host.py" and "client.ino" are not neccessary to make the program run, but they are useful for debugging if required
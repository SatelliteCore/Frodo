#include<SD.h>
#include <SPI.h>
//must be Ethernet2.h, as opposed to Ethernet.h
#include <Ethernet2.h>
//mac address can be randomly assigned for ethernet shield
byte mac[] = {0xB0, 0xCD, 0xAE, 0x0F, 0xDE, 0x10};

//to find ip address on computer (server), type "ipconfig" into CMD, look at "Ethernet adapter Ethernet:" and find
//"Autoconfiguration IPv4 Address:" and enter the ip address
//server ip address should also match the ip address in the host code, "host.py"
IPAddress server(169, 254, 95, 36); //server ip for Andrew-Laptop

//for the client, taking the server number and incrimenting the last didget by one usually works"
//example: 169,254,95,36 for host ip address, client would be 169,254,95,37
IPAddress ip(169, 254, 95, 37); //client ip for Andrew-Laptop

EthernetClient client;
void setup() {
  //Begin serial connection
  Serial.begin(9600);
  //initialize SD card
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);
  Serial.print("Starting SD..");
  if (!SD.begin(4)) Serial.println("failed");
  else Serial.println("ok");
  Ethernet.begin(mac, ip);
  //delay to give time for the ethernet shield to inizialize
  delay(1000);
  //server is the ip address, 12345 is the port number
  //both numbers should match host ip and port number in "host.py"
  if (client.connect(server, 12345)) {
    Serial.println("Connected");
  } else {
    Serial.println("Connection failed");
  }
}
void loop() {
  if (client) {
    //opens file "Img.png" as a readfile
    //default is first directory, change by adding "/folder/Img.png"
    File myFile = SD.open("Img.png", FILE_READ);
    while (myFile.available()) {
      //client writes to host the binary data of the file one byte at a time, expect 4-6 minutes depending on the picture
      //4-6 minutes for smaller files, larger files obviously take longer
      client.write(myFile.read());
    }
    //when sent, python code will recognize that the entire file was sent, and it will save the file and close comm
    client.write("");
    client.write("Done");
  }
}

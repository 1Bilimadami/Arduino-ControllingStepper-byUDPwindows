/**********************************************************************************************************************
Thıs program is pre version of final software. This SW is only including basic liblary commands

*Readme: With this program, switching run of stepper motor is possible with UDP Python client program. 
For that, i configured feather as a server and i plug in ethernet cable to my computer. 
And ip adress of feather(arduino) server is 192.168.178.177. So when we run firstly arduino server code then client code
both of server-client relations works.

Note: I needed to configuration of ethernet cable settings from windows network sharing center because ethernet
cable ip adress was not appropriate so i did 192.168.178.176
***********************************************************************************************************************/
#include <Ethernet.h> //Load Ethernet Library
#include <EthernetUdp.h> //Load UDP Library
#include <SPI.h> //Load the SPI Library
#include <Wire.h>
#include <Adafruit_MotorShield.h>
/**********************************************************************************************************************
*                                       Assign Motor types variable
***********************************************************************************************************************/
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *myMotorStepper = AFMS.getStepper(200, 2);//Stepper motor uses M3 & M4( M1&M2 is 1)

/**********************************************************************************************************************
*                                        MAC address and IP address.
***********************************************************************************************************************/
byte mac[] = { 0x98, 0x76, 0xB6, 0x12, 0x0b, 0x46 }; //physical hardware mac address of featherwing ethernet 
//IPAddress ip(192, 168, 178, 177); //Assign my IP adress // 
byte ip[] = { 192, 168, 178, 177 }; // ip in lan 
//(after "Run" the program open serial monitor then )
//byte gateway[] = { 192, 168, 178, 1 }; // internet access via router
//byte subnet[] = { 255, 255, 0, 0 }; //subnet mask

/**********************************************************************************************************************
*                                                 Shared variables
***********************************************************************************************************************/
unsigned int localPort = 5000; //Assign a Port to talk over
char packetBuffer[UDP_TX_PACKET_MAX_SIZE];
String datReq; //String for our data
int packetSize; //Size of Packet
EthernetUDP Udp; //Define UDP Object

//EthernetServer server(80); //not necessary because new port is 5000
void setup() {
Serial.begin(9600); //Turn on Serial Port
/**********************************************************************************************************************
*                                        Start the Ethernet connection and the server:
***********************************************************************************************************************/
Ethernet.begin(mac, ip); //Initialize Ethernet // or Ethernet.begin(mac, ip, gateway, subnet);
Udp.begin(localPort); //Initialize Udp
delay(1000); //delay
//server.begin(); check because without server.begin?
Serial.print("server is at ");
//Serial.println(Ethernet.localIP()); not sure about this code?
/**********************************************************************************************************************
*                                            Include Stepper setup
***********************************************************************************************************************/

AFMS.begin();  // create with the default frequency 1.6KHz
myMotorStepper->setSpeed(10);//Set Stepper Speed
}

/**********************************************************************************************************************
*                                                Main loop
***********************************************************************************************************************/
void loop() {
  
  packetSize = Udp.parsePacket(); //Read theh packetSize*** gelen giden paket var mı if'i icin kullanilabilir.
  if(packetSize>0){ //Check to see if a request is present***bu if yani. Burada "busy" degiskeni tanimlanabilir.
  
  Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE); //Reading the data request on the Udp
  String datReq(packetBuffer); //Convert packetBuffer array to string datReq
  Serial.println(datReq); //print to serial monitor for debuging?????????????????????????????removable
  
  if (datReq =="on") { //If switch forward was requested for stepper motor
  
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());  //Initialize Packet send
    Udp.print("You are Asking for switch forwared for stepper motor"); //Send string back to client 
     myMotorStepper->step(100, FORWARD, INTERLEAVE);
  delay(100);
    Udp.endPacket(); //Packet has been sent
  }
   if (datReq =="back") { //If switch backward was requested for stepper motor
  
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());  //Initialize Packet send
    Udp.print("You are Asking for switch back for stepper motor"); //Send string back to client 
      myMotorStepper->step(100, BACKWARD, MICROSTEP);
    delay(100);
    Udp.endPacket(); //Packet has been sent
   }
    if (datReq =="microstep") { ////If microstep was requested for stepper motor
  
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());  //Initialize Packet send
    Udp.print("You are Asking for switch microstep for stepper motor"); //Send string back to client 
      myMotorStepper->step(50, FORWARD, MICROSTEP);
    delay(1000);
    Udp.endPacket(); //Packet has been sent
    }
  }//check this paranthesis?
  memset(packetBuffer, 0, UDP_TX_PACKET_MAX_SIZE); 
  //data request from client might be in different size of arrays such as on/back/microstep so we need to clean them
}

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"


int pinValues5;
int pinValues6;
int pinValues7;
int pinValues8;


int seuil5 = 3;
int seuil6 = 3;
int seuil7 = 3;
int seuil8 = 3;


SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

void printDetail(uint8_t type, int value);

void setup() {

  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);


  mySoftwareSerial.begin(9600);
  Serial.begin(115200);

  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true);
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms

  myDFPlayer.volume(20);
}

void loop() {
  
  pinValues5 = readCapacitivePin(5);
  pinValues6 = readCapacitivePin(6);
  pinValues7 = readCapacitivePin(7);
  pinValues8 = readCapacitivePin(8);
 
   if (pinValues5 >= seuil5 && pinValues6 < seuil6 && pinValues7 < seuil7 && pinValues8 < seuil8) {

myDFPlayer.start();  
  delay(10);
  } 

  if (pinValues5 < seuil5 && pinValues6 >= seuil6 && pinValues7 < seuil7 && pinValues8 < seuil8) { 

myDFPlayer.pause();  
  delay(10);
    
  }

  if (pinValues5 < seuil5 && pinValues6 < seuil6 && pinValues7 >= seuil7 && pinValues8 < seuil8) { 
myDFPlayer.next();  
  delay(10);
    
  } 

   if (pinValues5 < seuil5 && pinValues6 < seuil6 && pinValues7 < seuil7 && pinValues8 >= seuil8) { 
myDFPlayer.previous(); 
  delay(10);
    
  }

   Serial.print("sensor—5 = ");
  Serial.println(pinValues5);
  Serial.print("\t");
   Serial.print("sensor—6 = ");
  Serial.println(pinValues6);
  Serial.print("\t");
   Serial.print("sensor—7 = ");
  Serial.println(pinValues7);
  Serial.print("\t");
   Serial.print("sensor_8 = ");
  Serial.print(pinValues8);
  Serial.print("\t");

  
}

//Les librairies nécessaires: 
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

//La zone conductrice sont connectées aux pins suivantes
int pinValues5;
int pinValues6;
int pinValues7;

//Leurs seuils : 
int seuil5 = 3;
int seuil6 = 3;
int seuil7 = 3;

// Le MP3 est connecté au pin D10 et D11.
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

void printDetail(uint8_t type, int value);

void setup() {

  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);


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

// Si la pin passe au dessus de son seuil, alors on execute l'ordre en dessous.
   if (pinValues5 >= seuil5 && pinValues6 < seuil6 && pinValues7 < seuil7) {

myDFPlayer.play(3);  
  delay(10);
  } 

  if (pinValues5 < seuil5 && pinValues6 >= seuil6 && pinValues7 < seuil7) { 

myDFPlayer.play(2);  
  delay(10);
    
  }

  if (pinValues5 < seuil5 && pinValues6 < seuil6 && pinValues7 >= seuil7) { 
myDFPlayer.play(1);  
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

  
}

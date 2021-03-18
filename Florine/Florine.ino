//Les librairies nécessaires: 
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

//Les zones conductrices sont connectées aux zones : 
int pinValues2;
int pinValues3;
int pinValues4;
int pinValues5;

// Leurs seuils : 
int seuil2 = 3;
int seuil3 = 3;
int seuil4 = 3;
int seuil5 = 3;

// Le MP3 est connecté au pin D10 et D11. 
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

void printDetail(uint8_t type, int value);

void setup() {
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);

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
// Si la pin concernée passe au dessus de son seuil, alors elle éxécute l'ordre en dessous.
  
  pinValues2 = readCapacitivePin(2);
  pinValues3 = readCapacitivePin(3);
  pinValues4 = readCapacitivePin(4);
  pinValues5 = readCapacitivePin(5);
 

  if (pinValues2>= seuil2 && pinValues3< seuil3 && pinValues4< seuil4 && pinValues5 < seuil5) { 
myDFPlayer.play(1);  
  delay(10);
  }
  
  if (pinValues2 < seuil2 && pinValues3 >= seuil3 && pinValues4 < seuil4 && pinValues5 < seuil5) {
   myDFPlayer.play(2);  
  delay(10);
  }
  
  if (pinValues2 < seuil2 && pinValues3 < seuil3 && pinValues4 >= seuil4 && pinValues5 < seuil5) {
myDFPlayer.play(3);  
  delay(10);
  }
  
   if (pinValues2 < seuil2 && pinValues3 < seuil3 && pinValues4 < seuil4 && pinValues5 >= seuil5) {
myDFPlayer.play(4);  
  delay(10);
  } 
  

  Serial.print("sensor—2 = ");
  Serial.print(pinValues2);
  Serial.print("\t");
  Serial.print("sensor_3 = ");
  Serial.print(pinValues3);
  Serial.print("\t");
  Serial.print("sensor—4 = ");
  Serial.println(pinValues4);
  Serial.print("\t");
   Serial.print("sensor—5 = ");
  Serial.println(pinValues5);
  Serial.print("\t");


  
}

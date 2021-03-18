//Les librairies nécessaires: 
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

//La zone conductrice est connectée à la pin D2. 
int pinValues2;

int seuil2 = 3;

// Le MP3 est connecté au pin D10 et D11. 
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

void printDetail(uint8_t type, int value);

void setup() {
  pinMode(2, INPUT);
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
// Si la pin D2 passe au dessus de son seuil, alors elle joue le MP3 suivant.
  pinValues2 = readCapacitivePin(2);
  if (pinValues2>= seuil2) { 

myDFPlayer.next(); 
  delay(10);
  }

  Serial.print("sensor—2 = ");
  Serial.print(pinValues2);
  Serial.print("\t");
 
}

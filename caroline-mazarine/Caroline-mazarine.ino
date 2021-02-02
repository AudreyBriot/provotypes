//Les librairies nécessaires: 
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

//Les zones conductrices sont connectées au pins suivantes
int pinValues2;
int pinValues3;
int pinValues4;
int pinValues5;
int pinValues6;
int pinValues7;


//leurs seuils : 
int seuil2 = 3;
int seuil3 = 3;
int seuil4 = 3;
int seuil5 = 3;
int seuil6 = 3;
int seuil7 = 3;


// Le MP3 est connecté au pin D10 et D11. 
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

void printDetail(uint8_t type, int value);

void setup() {
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
 

  mySoftwareSerial.begin(9600);
  Serial.begin(115200);

  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
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
// Si la pin passe au dessus de son seuil, alors elle execute l'ordre en dessous.
  
  pinValues2 = readCapacitivePin(2);
  pinValues3 = readCapacitivePin(3);
  pinValues4 = readCapacitivePin(4);
  pinValues5 = readCapacitivePin(5);
  pinValues6 = readCapacitivePin(6);
  pinValues7 = readCapacitivePin(7);

//pin D2
  if (pinValues2>= seuil2 && pinValues3< seuil3 && pinValues4< seuil4 && pinValues5 < seuil5 && pinValues6 < seuil6 && pinValues7 < seuil7) { 

myDFPlayer.play(1);  
  delay(10);
  }

//pin D3
  if (pinValues2 < seuil2 && pinValues3 >= seuil3 && pinValues4 < seuil4 && pinValues5 < seuil5 && pinValues6 < seuil6 && pinValues7 < seuil7) {

myDFPlayer.pause();  
  delay(10);
  }
  
//pin D4 
  if (pinValues2 < seuil2 && pinValues3 < seuil3 && pinValues4 >= seuil4 && pinValues5 < seuil5 && pinValues6 < seuil6 && pinValues7 < seuil7) {

myDFPlayer.next();  
  delay(10);
  }

//pin D5
   if (pinValues2 < seuil2 && pinValues3 < seuil3 && pinValues4 < seuil4 && pinValues5 >= seuil5 && pinValues6 < seuil6 && pinValues7 < seuil7) {

myDFPlayer.previous();  
  delay(10);
  } 
  
// pin D6, l'aile droite
  if (pinValues2 < seuil2 && pinValues3< seuil3 && pinValues4< seuil4 && pinValues5 < seuil5 && pinValues6 >= seuil6 && pinValues7 < seuil7) { 

myDFPlayer.play(20);  //au lieu de 20 tu peux entrer le numéro de ta chanson
  delay(10);
  }
  
// pin D7, l'aile gauche
  if (pinValues2 < seuil2 && pinValues3< seuil3 && pinValues4< seuil4 && pinValues5 < seuil5 && pinValues6 < seuil6 && pinValues7 >= seuil7) { 

myDFPlayer.play(21);  //au lieu de 20 tu peux entrer le numéro de ta chanson
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
   Serial.print("sensor—6 = ");
  Serial.println(pinValues6);
  Serial.print("\t");
   Serial.print("sensor—7 = ");
  Serial.println(pinValues7);
  Serial.print("\t");


  
}

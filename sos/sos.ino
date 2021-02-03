const int numberOfKeys = 7;
int keys[numberOfKeys] = { 2, 3, 4, 5, 6, 7, 8 };
int notes[numberOfKeys] = { 1760, 2093, 2349, 2262, 2880, 2033, 2040 };

int speaker = 9;
int touchValue;
int touchValue7;



void setup() {
  pinMode(speaker, OUTPUT);
  int i = 0;
  while (i < numberOfKeys)  //set the piano keys to be inputs
  {
    pinMode(keys[i], INPUT);
    i = i + 1;
  }
  Serial.begin(115200); // initialize the communication
}

void loop() {
  int i = 0;
  while (i < numberOfKeys)
  {
    checkPianoKey(keys[i], notes[i]);
    i = i + 1;
  }
  checkpianoperculiar();
  Serial.println();
  delay(100);
}

void checkPianoKey(int key, int note) {
  touchValue = readCapacitivePin(key); //read touch sensor value
  Serial.print(touchValue); //send value to the computer
 Serial.print("\t"); //send a tab
  if (touchValue > 3) //if the key is pressed
  {
    tone(speaker, note); // play a note
    delay(100); // wait for 1/10th of a second
  }
  else  // if the key is not pressed
  {
    noTone(speaker); // stop playing the note
  }
}
/////

void checkpianoperculiar() {
  touchValue = readCapacitivePin(7); //read touch sensor value
  Serial.print(touchValue7); //send value to the computer
  Serial.print("\t"); //send a tab
  if (touchValue > 3) //if the key is pressed
  {
    tone(speaker, 2006); // play a note
    delay(100); // wait for 1/10th of a second
  }
  else  // if the key is not pressed
  {
    noTone(speaker); // stop playing the note
  }
}


////////

// readCapacitivePin

//  Input: Arduino pin number
//  Output: A number, from 0 to 17 expressing
//  how much capacitance is on the pin
//  When you touch the pin, or whatever you have
//  attached to it, the number will get higher

#include "pins_arduino.h" // Arduino pre-1.0 needs this

uint8_t readCapacitivePin(int pinToMeasure) {

  // Variables used to translate from Arduino to AVR pin naming

  volatile uint8_t* port;

  volatile uint8_t* ddr;

  volatile uint8_t* pin;

  // Here we translate the input pin number from
  //  Arduino pin number to the AVR PORT, PIN, DDR,
  //  and which bit of those registers we care about.

  byte bitmask;

  port = portOutputRegister(digitalPinToPort(pinToMeasure));

  ddr = portModeRegister(digitalPinToPort(pinToMeasure));

  bitmask = digitalPinToBitMask(pinToMeasure);

  pin = portInputRegister(digitalPinToPort(pinToMeasure));

  // Discharge the pin first by setting it low and output

  *port &= ~(bitmask);

  *ddr  |= bitmask;

  delay(1);

  uint8_t SREG_old = SREG; //back up the AVR Status Register

  // Prevent the timer IRQ from disturbing our measurement

  noInterrupts();

  // Make the pin an input with the internal pull-up on

  *ddr &= ~(bitmask);

  *port |= bitmask;

  // Now see how long the pin to get pulled up. This manual unrolling of the loop
  // decreases the number of hardware cycles between each read of the pin,
  // thus increasing sensitivity.

  uint8_t cycles = 17;

  if (*pin & bitmask) {
    cycles =  0;
  }

  else if (*pin & bitmask) {
    cycles =  1;
  }

  else if (*pin & bitmask) {
    cycles =  2;
  }

  else if (*pin & bitmask) {
    cycles =  3;
  }

  else if (*pin & bitmask) {
    cycles =  4;
  }

  else if (*pin & bitmask) {
    cycles =  5;
  }

  else if (*pin & bitmask) {
    cycles =  6;
  }

  else if (*pin & bitmask) {
    cycles =  7;
  }

  else if (*pin & bitmask) {
    cycles =  8;
  }

  else if (*pin & bitmask) {
    cycles =  9;
  }

  else if (*pin & bitmask) {
    cycles = 10;
  }

  else if (*pin & bitmask) {
    cycles = 11;
  }

  else if (*pin & bitmask) {
    cycles = 12;
  }

  else if (*pin & bitmask) {
    cycles = 13;
  }

  else if (*pin & bitmask) {
    cycles = 14;
  }

  else if (*pin & bitmask) {
    cycles = 15;
  }

  else if (*pin & bitmask) {
    cycles = 16;
  }

  // End of timing-critical section; turn interrupts back on if they were on before, or leave them off if they were off before

  SREG = SREG_old;

  // Discharge the pin again by setting it low and output
  //  It's important to leave the pins low if you want to
  //  be able to touch more than 1 sensor at a time - if
  //  the sensor is left pulled high, when you touch
  //  two sensors, your body will transfer the charge between
  //  sensors.

  *port &= ~(bitmask);
  *ddr  |= bitmask;

  return cycles;

}

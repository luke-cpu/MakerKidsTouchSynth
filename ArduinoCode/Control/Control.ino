
//***SD CARD INITIALIZATIONS***//
#include "SD.h"
#include "TMRpcm.h"
#include "SPI.h" // SD Card libraries
#define SD_ChipSelectPin 10 // Where CS of SD Card breakout is connected
TMRpcm tmrpcm;



//***CAPACITIVE TOUCH INITIALIZATIONS***//
#include <Wire.h>
#include "Adafruit_MPR121.h" // Capacitive touch libraries
#include "pitches.h"

int scale1 [] = {NOTE_A4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6, NOTE_D6, NOTE_E6};

#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

Adafruit_MPR121 cap = Adafruit_MPR121();
uint16_t lasttouched = 0;
uint16_t currtouched = 0;


//***BOTTON MODE INITIALIZATIONS***//
int buttonPin = 2; // Pin variables

int currentState;
int previousState = LOW; // State variables

int debounceDelay = 10; // Debounce variables

int mode = 1; // Mode variables



void setup(){
//***SD CARD SETUP***//
  Serial.begin(9600);
  tmrpcm.speakerPin=9;
  if(!SD.begin(SD_ChipSelectPin)){ // Checks if SD Card breakout is connected to the CS pin correctly
    Serial.println("SD fail");
    return;
  }
  tmrpcm.setVolume(5); // Sets volume of speaker *goes up to 10, but 6 is max for our set up*
  //tmrpcm.play("test.wav"); // A test wav file currently in the sd card; not connected to a capacitive touch and plays upon startup
  while (!Serial) { // needed to keep Arduino from starting up too fast
    delay(100);
  }

//***CAPACITIVE TOUCH SETUP***//
  Serial.println("Adafruit MPR121 Capacitive Touch sensor test"); 
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");

//***BOTTON MODE SETUP***//
  pinMode(buttonPin, INPUT);
  
}



void loop() {
  // put your main code here, to run repeatedly:
  
  currentState = digitalRead(buttonPin);
  if((currentState == LOW) && (previousState == HIGH)) // If button is depressed
  {
    switch(mode)
    {
      case 1: mode = 2;
      //Serial.println("Mode "); Serial.print(mode);
      //Serial.print(F("\n"));
        break;
      case 2: mode = 3;
      //Serial.println("Mode "); Serial.print(mode);
      //Serial.print(F("\n"));
        break;
      case 3: mode = 1;
      //Serial.println("Mode "); Serial.print(mode);
      //Serial.print(F("\n"));
        break;
      default: mode = 1;
      //Serial.println("Mode "); Serial.print(mode);
      //Serial.print(F("\n"));
    }
  }
  previousState = currentState;
  //Serial.print(mode);
  //Serial.print(F("\n"));
  delay(debounceDelay);


  if(mode == 1){
    currtouched = cap.touched();
    Serial.write(currtouched + 1);
    for (uint8_t i=0; i<12; i++) {
      // if it *is* touched and *wasnt* touched before, alert!
      if ((currtouched & _BV(i)) && !(lasttouched & _BV(i))) {
        //Serial.print(i); Serial.println(" touched");
        //Serial.write(i);
        tone(9, scale1[i]); 
      }
      // if it *was* touched and now *isnt*, alert!
      if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
        //Serial.print(i); Serial.println(" released");
        noTone(9);
      }
    }
    lasttouched = currtouched;   // reset our state
    return;
  }

  else if(mode == 2){
    currtouched = cap.touched();
    Serial.write(currtouched + 1);
    for (uint8_t i=0; i<12; i++) {
      // it if *is* touched and *wasnt* touched before, alert!
      if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
        //Serial.print(i); Serial.println(" touched");
        //Serial.write(i);
        if(i == 0){
          tmrpcm.play("0.wav");
        }
        else if(i == 1){
          tmrpcm.play("1.wav");
        }
        else if(i == 2){
          tmrpcm.play("2.wav");
        }
        else if(i == 3){
          tmrpcm.play("3.wav");
        }
        else if(i == 4){
          tmrpcm.play("4.wav");
        }
        else if(i == 5){
          tmrpcm.play("5.wav");
        }
        else if(i == 6){
          tmrpcm.play("6.wav");
        }
        else if(i == 7){
          tmrpcm.play("7.wav");
        }
      }
      // if it *was* touched and now *isnt*, alert!
      if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
        //Serial.print(i); Serial.println(" released");
        tmrpcm.stopPlayback();
      }
    }
    lasttouched = currtouched; // reset our state
    return;
  }

  else if(mode == 3){                 //mode 3: chords in C major scale
    currtouched = cap.touched();
    Serial.write(currtouched + 1);
    for (uint8_t i=0; i<12; i++) {
      // it if *is* touched and *wasnt* touched before, alert!
      if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
        //Serial.print(i); Serial.println(" touched");
        //Serial.write(i);
        if(i == 0){       //Cmajor
          tone(9, NOTE_C5); //duration of 200 ms each note
          delay(200);
          noTone(9);
          tone(9, NOTE_E5);
          delay(200);
          noTone(9);
          tone(9, NOTE_G5);
          delay(200);
          noTone(9);
        }
        else if(i == 1){  //Dminor
          tone(9, NOTE_D5);
          delay(200);
          noTone(9);
          tone(9, NOTE_F5);
          delay(200);
          noTone(9);
          tone(9, NOTE_A5);
          delay(200);
          noTone(9);
        }
        else if(i == 2){  //Eminor
          tone(9, NOTE_E5);
          delay(200);
          noTone(9);
          tone(9, NOTE_G5);
          delay(200);
          noTone(9);
          tone(9, NOTE_B5);
          delay(200);
          noTone(9);
        }
        else if(i == 3){  //Fmajor
          tone(9, NOTE_F5);
          delay(200);
          noTone(9);
          tone(9, NOTE_A5);
          delay(200);
          noTone(9);
          tone(9, NOTE_C6);
          delay(200);
          noTone(9);
        }
        else if(i == 4){  //Gmajor
          tone(9, NOTE_G5);
          delay(200);
          noTone(9);
          tone(9, NOTE_B5);
          delay(200);
          noTone(9);
          tone(9, NOTE_D6);
          delay(200);
          noTone(9);
        }
        else if(i == 5){  //Aminor
          tone(9, NOTE_A5);
          delay(200);
          noTone(9);
          tone(9, NOTE_C6);
          delay(200);
          noTone(9);
          tone(9, NOTE_E6);
          delay(200);
          noTone(9);
        }
        else if(i == 6){  //Bdim
          tone(9, NOTE_B5);
          delay(200);
          noTone(9);
          tone(9, NOTE_D6);
          delay(200);
          noTone(9);
          tone(9, NOTE_F6);
          delay(200);
          noTone(9);
        }
        else if(i == 7){ 
          tone(9, NOTE_C6); //duration of 500 ms each note
          delay(200);
          noTone(9);
          tone(9, NOTE_E6);
          delay(200);
          noTone(9);
          tone(9, NOTE_G6);
          delay(200);
          noTone(9);
        }
      }
      // if it *was* touched and now *isnt*, alert!
     if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
        //Serial.print(i); Serial.println(" released");
        return;
      }
    }
    //lasttouched = currtouched; // reset our state
  }
}

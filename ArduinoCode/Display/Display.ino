#include <RGBmatrixPanel.h>
#include <math.h>

#define CLK  8 
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2

RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

// Similar to F(), but for PROGMEM string pointers rather than literals
#define F2(progmem_ptr) (const __FlashStringHelper *)progmem_ptr

//const char str[] PROGMEM = "Mode 1";
const char mode1Str[] PROGMEM = "Mode 1";
const char mode2Str[] PROGMEM = "Mode 2";
const char mode3Str[] PROGMEM = "Mode 3";
const char mode4Str[] PROGMEM = "Mode 4";
int16_t    textX         = matrix.width(),
           textMin       = sizeof(mode1Str) * -12,
           hue           = 0;

// Pin variables
int buttonPin = 11;

// State variables
int currentState;
int previousState = LOW;

// Debounce variables
int debounceDelay = 10;

// Mode variables
int previousMode;
int mode = 1;
int prevMode = 0;

int receiverData;
int j;
int shape = 0;
int prevData = 0;

void setup() {
  matrix.begin();
  //delay(1000);
  
//  matrix.setTextWrap(false); // Allow text to run off right edge
//  matrix.setTextSize(2);
  Serial.begin(9600);
  
}

void loop() {
  if (Serial.available() > 0) {
    receiverData = Serial.read();
    switch(mode)
    {
      case 1:
        if(receiverData > 1)
        {
          receiverData = receiverData-1;
          receiverData = log(receiverData)/log(2);
          matrix.fillRect(((receiverData*4)), 8, 4, 16, matrix.Color333(1,1,1));
          matrix.fillRect(((receiverData*4)+1), 0, 2, 16, matrix.Color333(1,1,1));
        }
      break;
      case 2:
        if(receiverData > 1)
        {
          switch(shape)
          {
            case 0:
              matrix.fillCircle(10,10,5,matrix.Color333(2,0,0));
            break;
            case 1:
              matrix.fillCircle(10,10,5,matrix.Color333(0,3,0));
            break;
            case 2:
              matrix.fillCircle(10,10,5,matrix.Color333(0,0,2));
            break;
            case 3:
              matrix.fillCircle(10,10,5,matrix.Color333(3,2,0));
            break;
            case 4:
              matrix.fillRect(10,10,5,5,matrix.Color333(2,0,0));
            break;
            case 5:
              matrix.fillRect(10,10,5,5,matrix.Color333(0,2,0));
            break;
            case 6:
              matrix.fillRect(10,10,5,5,matrix.Color333(0,0,2));
            break;
            case 7:
              matrix.fillRect(10,10,5,5,matrix.Color333(2,2,0));
            break;
            case 8:
              matrix.drawLine(0, 0, 31, 15, matrix.Color333(2, 0, 0));
              matrix.drawLine(31, 0, 0, 15, matrix.Color333(2, 0, 0));
            break;
            case 9:
              matrix.drawLine(0, 0, 31, 15, matrix.Color333(3, 0, 3));
              matrix.drawLine(31, 0, 0, 15, matrix.Color333(2, 0, 2));
            break;
            case 10:
              matrix.drawLine(0, 0, 31, 15, matrix.Color333(2, 2, 0));
              matrix.drawLine(31, 0, 0, 15, matrix.Color333(3, 2, 0));
            break;
            case 11:
              matrix.drawLine(0, 0, 31, 15, matrix.Color333(0, 3, 2));
              matrix.drawLine(31, 0, 0, 15, matrix.Color333(0, 3, 2));
            break;
          }
          if((receiverData != prevData) && (shape<=11)) shape++;
          else if(receiverData!= prevData) shape = 0;
          prevData = receiverData;
        }
      break;
      case 3:
      if(receiverData>1)
      {
        receiverData = receiverData-1;
        receiverData = log(receiverData)/log(2);
      
        switch(receiverData)
        {
          case 0: // 0 
            matrix.fillRect(0, 0, 1, 16, matrix.Color333(7,0,0));
            delay(200);
            matrix.fillRect(1, 0, 2, 16, matrix.Color333(7,0,0));
            delay(200);
            matrix.fillRect(3, 0, 1, 16, matrix.Color333(7,0,0));
            delay(200);
          break;
          case 1: // 1
            matrix.fillRect(4, 0, 1, 16, matrix.Color333(0,7,0));
            delay(200);
            matrix.fillRect(5, 0, 2, 16, matrix.Color333(0,7,0));
            delay(200);
            matrix.fillRect(7, 0, 1, 16, matrix.Color333(0,7,0));
            delay(200);
          break;
          case 2: // 2
            matrix.fillRect(8, 0, 1, 16, matrix.Color333(0,7,7));
            delay(200);
            matrix.fillRect(9, 0, 2, 16, matrix.Color333(0,7,7));
            delay(200);
            matrix.fillRect(11, 0, 1, 16, matrix.Color333(0,7,7));
            delay(200);
          break;
          case 3: // 3
            matrix.fillRect(12, 0, 1, 16, matrix.Color333(7,7,0));
            delay(200);
            matrix.fillRect(13, 0, 2, 16, matrix.Color333(7,7,0));
            delay(200);
            matrix.fillRect(15, 0, 1, 16, matrix.Color333(7,7,0));
            delay(200);
          break;
          case 4: // 4
            matrix.fillRect(16, 0, 1, 16, matrix.Color333(0,0,7));
            delay(200);
            matrix.fillRect(17, 0, 2, 16, matrix.Color333(0,0,7));
            delay(200);
            matrix.fillRect(19, 0, 1, 16, matrix.Color333(0,0,7));
            delay(200);
          break;
          case 5: // 5
            matrix.fillRect(20, 0, 1, 16, matrix.Color333(7,0,7));
            delay(200);
            matrix.fillRect(21, 0, 2, 16, matrix.Color333(7,0,7));
            delay(200);
            matrix.fillRect(23, 0, 1, 16, matrix.Color333(7,0,7));
            delay(200);
          break;
          case 6: // 6
            matrix.fillRect(24, 0, 1, 16, matrix.Color333(1,1,1));
            delay(200);
            matrix.fillRect(25, 0, 2, 16, matrix.Color333(1,1,1));
            delay(200);
            matrix.fillRect(27, 0, 1, 16, matrix.Color333(1,1,1));
            delay(200);
          break;
          case 7: // 7
            matrix.fillRect(28, 0, 1, 16, matrix.Color333(0,2,5));
            delay(200);
            matrix.fillRect(29, 0, 2, 16, matrix.Color333(0,2,5));
            delay(200);
            matrix.fillRect(31, 0, 1, 16, matrix.Color333(0,2,5));
            delay(200);
          break;
          default: matrix.fillScreen(0);
        }
      }
      break;
    }
  }
  else
  {
  byte i;
  // Clear background
  matrix.fillScreen(0);
  currentState = digitalRead(buttonPin);
  if((currentState == LOW) && (previousState == HIGH)) // If button is depressed
  {
    switch(mode) // Cycle to the next mode
    {
      case 1: mode=2;
        break;
      case 2: mode=3;
        break;
      case 3: mode=1;
        break;
      default: mode=1;
    }
  }
  previousState = currentState;
  delay(debounceDelay);

  if(prevMode != mode)
  {
    matrix.setCursor(1,0);
    matrix.setTextSize(1);
    matrix.setTextColor(matrix.Color333(7,0,0));
    switch(mode)
    {
      case 1:
        matrix.print("Mode 1");
        delay(1000);
      break;
      case 2:
        matrix.print("Mode 2");
        delay(1000);
      break;
      case 3:
        matrix.print("Mode 3");
        delay(1000);
      break;
      case 4:
        matrix.print("Mode 4");
        delay(1000);
      break;
    }
  }
  prevMode = mode;
//  
//  // Draw big scrolly text on top
////  matrix.setTextColor(matrix.ColorHSV(hue, 255, 255, true));
////  matrix.setCursor(textX, 1);
////  switch(mode) // Display the current mode
////  {
////    case 1: matrix.print(F2(mode1Str));
////      break;
////    case 2: matrix.print(F2(mode2Str));
////      break;
////    case 3: matrix.print(F2(mode3Str));
////      break;
////    default: matrix.print(F2(mode1Str));
////  }
//
//  // Move text left (w/wrap), increase hue
//  //if((--textX) < textMin) textX = matrix.width();
//
////#if !defined(__AVR__)
////  // On non-AVR boards, delay slightly so screen updates aren't too quick.
////  delay(20);
////#endif
////
//  // Update display
  //matrix.swapBuffers(false);

  }
  if(mode==1||mode==2) delay(1);
}

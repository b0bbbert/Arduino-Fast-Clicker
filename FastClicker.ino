//Emulates a left mouse button auto-clicker
//For Arduino Leonardo
//Press the button once to turn on the clicker and LED
//Press the button again to turn off the clicker and LED
//Requires use of the Mouse library

#include <Mouse.h>

// set pin numbers for the button and light:
// Pin 2 for LED see reference https://www.arduino.cc/en/Tutorial/Blink
// Pin 7 for button see reference: https://www.arduino.cc/en/Tutorial/KeyboardAndMouseControl
const int mouseButton = 7;
const int ledLight = 2;

//Sets flags and delays on the button
boolean isClicking = false;
const int buttonDelay = 500;  // in milliseconds
const int clickPerSecond = 1;   // number of clicks per second 
const int loopSleep = 10;   // in milliseconds
int buttonDelayCnt = 0;
int clickDelayCnt = 0;

void setup() { 
  
  // initialize the button input and light output:
  pinMode(mouseButton, INPUT);
  pinMode(ledLight, OUTPUT);
  
  // initialize mouse control:
  Mouse.begin();
}

void loop() {
  int buttonDelayMax = buttonDelay/loopSleep;  
  int clickDelayMax = (1000/clickPerSecond)/loopSleep-1;
  int buttonDelayCnt = 0;
  int clickDelayCnt = 0;
  if(isClicking == true && clickDelayCnt == 0 )
  {
     Mouse.click(MOUSE_LEFT);
     clickDelayCnt = clickDelayMax;
  }  

  if (digitalRead(mouseButton) == HIGH && buttonDelayCnt == 0 ) {
    if(isClicking == true)
    {
      //Stops the clicker and turns off the LED
      isClicking = false;
      digitalWrite(ledLight, LOW);  
    }
    else
    {
       //Starts the clicker and turns on the LED
       isClicking = true;
       digitalWrite(ledLight, HIGH);  
    }
    
    buttonDelayCnt = buttonDelayMax;
  }

  //Delays the next button read
  if( buttonDelayCnt > 0)
    buttonDelayCnt--;

  //Delays the click speed
  if( clickDelayCnt > 0)
    clickDelayCnt--;
    
  delay(loopSleep);

}



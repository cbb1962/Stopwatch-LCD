/*
 Wiring based on: http://www.hobbytronics.co.uk/arduino-tutorial10-lcd

 The circuit:
 * LCD VSS pin to Ground
 * LCD VDD pin to +5vdc
 * LCD VO pin to Middle pin of Pot
 * LCD RS pin to digital pin 12
 * LCD R/W pin to Ground
 * LCD Enable pin to digital pin 11
 * LCD D0 pin not connected
 * LCD D1 pin not connected
 * LCD D2 pin not connected
 * LCD D3 pin not connected
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD A pin to +5vdc
 * LCD K pin to Ground

 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int ledPin = 13;                    // LED connected to digital pin 13
int buttonPin = 8;                  // button on pin 2

int value = LOW;                    // previous value of the LED
int buttonState;                    // variable to store button state
int lastButtonState;                // variable to store last button state
int blinking;                       // condition for blinking - timer is timing
int frameRate = 1;                // the frame rate (frames per second) at which the stopwatch runs - Change to suit
long interval = (1000/frameRate);   // blink interval
long previousMillis = 0;            // variable to store last time LED was updated
long startTime ;                    // start time for stop watch
long elapsedTime ;                  // elapsed time for stop watch
int fractional;                     // variable used to store fractional part of Frames
int fractionalSecs;                 // variable used to store fractional part of Seconds
int fractionalMins;                 // variable used to store fractional part of Minutes
int fractionalHours;                // variable used to store fractional part of Hours
int elapsedFrames;                  // elapsed frames for stop watch
int elapsedSeconds;                 // elapsed seconds for stop watch
int elapsedMinutes;                 // elapsed Minutes for stop watch
int elapsedHours;                   // elapsed Hours for stop watch
char buf[10];                       // string buffer for itoa function

void setup()
{
  lcd.begin(20, 4);                // intialise the LCD.
  pinMode(ledPin, OUTPUT);         // sets the digital pin as output
  pinMode(buttonPin, INPUT);       // not really necessary, pins default to INPUT anyway
  digitalWrite(buttonPin, HIGH);   // turn on pullup resistors. Wire button so that press shorts pin to ground.
lcd.setCursor(4,0);
  lcd.print("SOUS VIDE 2.0");
  lcd.setCursor(5,1);
  lcd.print("SET: 132.0 F");
  lcd.setCursor(2,2);
  lcd.print("ACTUAL: 131.6 F");
  lcd.setCursor(4,3);
  lcd.print("TIME: ");
  //lcd.setCursor(0,2);
}

void loop(){

  digitalWrite(ledPin, LOW);            // Initiate LED and Step Pin States

  buttonState = digitalRead(buttonPin); // Check for button press, read the button state and store

// check for a high to low transition if true then found a new button press while clock is not running - start the clock    
   if (buttonState == LOW && lastButtonState == HIGH  &&  blinking == false){
    startTime = millis();                               // store the start time
      blinking = true;                                  // turn on blinking while timing
      delay(10);                                         // short delay to debounce switch
      lastButtonState = buttonState;                    // store buttonState in lastButtonState, to compare next time 
   }

// check for a high to low transition if true then found a new button press while clock is running - stop the clock and report
   else if (buttonState == LOW && lastButtonState == HIGH && blinking == true){
   blinking = false;                                    // turn off blinking, all done timing
   lastButtonState = buttonState;                       // store buttonState in lastButtonState, to compare next time

   
// Routine to report elapsed time            
   elapsedTime =   millis() - startTime;                // store elapsed time
   elapsedHours = (elapsedTime / 3600000L);
   elapsedMinutes = (elapsedTime / 60000L);
   elapsedSeconds = (elapsedTime / 1000L);              // divide by 1000 to convert to seconds - then cast to an int to print
   elapsedFrames = (elapsedTime / interval);            // divide by 100 to convert to 1/100 of a second - then cast to an int to print
   fractional = (int)(elapsedFrames % frameRate);       // use modulo operator to get fractional part of 100 Seconds
   fractionalSecs = (int)(elapsedSeconds % 60L);        // use modulo operator to get fractional part of 60 Seconds
   fractionalMins = (int)(elapsedMinutes % 60L);        // use modulo operator to get fractional part of 60 Minutes
   fractionalHours = (int)(elapsedHours % 60L);        // use modulo operator to get fractional part of 60 Minutes   
   lcd.setCursor(9,3);
 //  lcd.clear();                                         // clear the LDC

 if (fractionalHours < 10){                            // pad in leading zeros
      lcd.print("0");                                 // add a zero
      }

    lcd.print(itoa(fractionalHours, buf, 10));       // convert the int to a string and print a fractional part of 60 Minutes to the LCD
      lcd.print(":");                                 //print a colan. 

 if (fractionalMins < 10){                            // pad in leading zeros
      lcd.print("0");                                 // add a zero
      }

 lcd.print(itoa(fractionalMins, buf, 10));          // convert the int to a string and print a fractional part of 60 Seconds to the LCD
   lcd.print(":");                                    //print a colan. 

 if (fractionalSecs < 10){                                // pad in leading zeros 
      lcd.print("0");                                 // add a zero
      }     

 lcd.print(itoa(fractionalSecs, buf, 10));              // convert the int to a string and print a fractional part of 25 Frames to the LCD
   }

 else{
      lastButtonState = buttonState;                  // store buttonState in lastButtonState, to compare next time
   }

// run commands at the specified time interval
// blink routine - blink the LED while timing
// check to see if it's time to blink the LED; that is, the difference
// between the current time and last time we blinked the LED is larger than
// the interval at which we want to blink the LED.        
                                     

 if ( (millis() - previousMillis > interval) ) {

    if (blinking == true){
       previousMillis = millis();                    // remember the last time we blinked the LED

       digitalWrite(ledPin, HIGH);                   // Pulse the LED for Visual Feedback

   elapsedTime =   millis() - startTime;                // store elapsed time
   elapsedHours = (elapsedTime / 3600000L);
   elapsedMinutes = (elapsedTime / 60000L);
   elapsedSeconds = (elapsedTime / 1000L);              // divide by 1000 to convert to seconds - then cast to an int to print
   elapsedFrames = (elapsedTime / interval);            // divide by 100 to convert to 1/100 of a second - then cast to an int to print
   fractional = (int)(elapsedFrames % frameRate);       // use modulo operator to get fractional part of 100 Seconds
   fractionalSecs = (int)(elapsedSeconds % 60L);        // use modulo operator to get fractional part of 60 Seconds
   fractionalMins = (int)(elapsedMinutes % 60L);        // use modulo operator to get fractional part of 60 Minutes
   fractionalHours = (int)(elapsedHours % 60L);         // use modulo operator to get fractional part of 60 Minutes   
   lcd.setCursor(9,3);
 //  lcd.clear();                                         // clear the LDC
       if (fractionalHours < 10){                     // pad in leading zeros
         lcd.print("0");                             // add a zero
         }

       lcd.print(itoa(fractionalHours, buf, 10));   // convert the int to a string and print a fractional part of 60 Minutes to the LCD
         lcd.print(":");                             //print a colan. 

       if (fractionalMins < 10){                     // pad in leading zeros 
         lcd.print("0");                             // add a zero
         }

       lcd.print(itoa(fractionalMins, buf, 10));   // convert the int to a string and print a fractional part of 60 Seconds to the LCD
         lcd.print(":");                             //print a colan. 

       if (fractionalSecs < 10){                         // pad in leading zeros 
         lcd.print("0");                             // add a zero
         }
          lcd.print(itoa((fractionalSecs), buf, 10));  // convert the int to a string and print a fractional part of 25 Frames to the LCD
         }

    else{
          digitalWrite(ledPin, LOW);                 // turn off LED when not blinking 
          }
 }

}

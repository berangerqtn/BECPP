#include <Arduino.h>
/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.
 
 modified 8 Nov 2013
 by Scott Fitzgerald
 https://arduino.cc/en/Tutorial/Sweep
*/
 
#include <Servo.h>
 
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
 
int pos = 0;    // variable to store the servo position
 
void setup() {
  myservo.attach(15);  // attaches the servo on pin 5 to the servo object
}
 
void loop() {
  for (pos = 0; pos <= 100; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos); 
    Serial.println(myservo.read());             // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 100; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    Serial.println(myservo.read());
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

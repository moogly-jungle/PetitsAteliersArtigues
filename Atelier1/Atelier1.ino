#include <Servo.h>
#include "music.h"
#include "RGB.h"


Servo myservo;  // create servo object to control a servo

int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin
int first;  //variable to make music one time
int valR,valG,valB;



void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object

  setupRGB();
}



void loop() {
  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  //l = 250;
  val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  myservo.write(val);                  // sets the servo position according to the scaled value

  if(val!=0 && val !=180)
    first=0;
  if((val==0 || val==180)&& first==0)
  {
    music();
    first=1;
  }
 
  if(val<60)
    color(val,0,0);
  if(val>=60 && val<120)
    color(0,val,0);
  if(val>=120)
    color(0,0,val);
  delay(15);                           // waits for the servo to get there
}


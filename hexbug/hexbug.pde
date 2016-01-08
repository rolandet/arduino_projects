
/* 
 * program to control hex bug spider
 *   can turn left/right
 *       move forward/back
 *   on B channel
 * 
 */
#include "hexbug.h"

int IRledPin =  13;

void setup()   {                
  pinMode(IRledPin, OUTPUT);       
  Serial.begin(9600);
}

void loop()                     
{
  Serial.println("Sending IR signal");
  delay(10000);
  circle();
  spin(RIGHT);
  move(FORWARD,10);
  move(LEFT,10);
  move(FORWARD,10);
  move(BACKWARD,20);
}

void pulseIR(long microsecs) { 
  cli();
  while (microsecs > 0) {
    // 38 kHz is about 13 microseconds high and 13 microseconds low
    digitalWrite(IRledPin, HIGH);  // this takes about 3 microseconds to happen
    delayMicroseconds(10);         // hang out for 10 microseconds
    digitalWrite(IRledPin, LOW);   // this also takes about 3 microseconds
    delayMicroseconds(10);         // hang out for 10 microseconds

    // so 26 microseconds altogether
    microsecs -= 26;
  } 
  sei();  // this turns them back on
}

void spin(Direction d) {
  int i=0;
  for(i=0; i< 80; i++ ) {
    switch ( d ) {
    case RIGHT :
      B_turnright();
      break;
    case LEFT :
      B_turnleft();
      break;
    }
  }
}

void circle() {
  move(FORWARD,4);
  move(RIGHT,2);
  move(FORWARD,4);
  move(RIGHT,2);
  move(FORWARD,4);
  move(RIGHT,2);
  move(FORWARD,4);
  move(RIGHT,2);
  move(FORWARD,4);
  move(RIGHT,2);
  move(FORWARD,4);
  move(RIGHT,2);
}


void move(Direction d, int steps) {
  int i;
  for (i=0; i< steps; i++) {
    switch ( d ) {
    case FORWARD :
      B_forward();
      break;
    case BACKWARD :
      B_backward();
      break;
    case LEFT :
      B_turnleft();
      break;
    case RIGHT :
      B_turnright();
      break;
    }
    delay(500);
  }
}

void B_forward() {
  Serial.println("Sending B_forward IR signal");
  pulseIR(1850);
  delayMicroseconds(550);
  pulseIR(1850);
  delayMicroseconds(1000);
  pulseIR(300);
  delayMicroseconds(1550);
  pulseIR(350);
  delayMicroseconds(600);
  pulseIR(350);
  delayMicroseconds(600);
  pulseIR(350);
  delayMicroseconds(600);
  pulseIR(350);
  delayMicroseconds(1550);
  pulseIR(350);
  delayMicroseconds(600);
  pulseIR(350);
  delayMicroseconds(1550);
  pulseIR(300);
  delayMicroseconds(1550);
  pulseIR(350);
  delayMicroseconds(1550);
  pulseIR(300);
  delayMicroseconds(650);
  pulseIR(350);
}

void B_backward() {
  Serial.println("Sending B_backward IR signal");
  pulseIR(1900);
  delayMicroseconds(500);
  pulseIR(1900);
  delayMicroseconds(1000);
  pulseIR(350);
  delayMicroseconds(600);
  pulseIR(350);
  delayMicroseconds(1550);
  pulseIR(300);
  delayMicroseconds(650);
  pulseIR(350);
  delayMicroseconds(650);
  pulseIR(300);
  delayMicroseconds(1550);
  pulseIR(350);
  delayMicroseconds(1600);
  pulseIR(300);
  delayMicroseconds(650);
  pulseIR(350);
  delayMicroseconds(1550);
  pulseIR(350);
  delayMicroseconds(1550);
  pulseIR(300);
  delayMicroseconds(650);
  pulseIR(350);
}

void B_turnleft() {
  Serial.println("Sending B_turnleft IR signal");
  pulseIR(1850);
  delayMicroseconds(550);
  pulseIR(1850);
  delayMicroseconds(1000);
  pulseIR(300);
  delayMicroseconds(1550);
  pulseIR(350);
  delayMicroseconds(1550);
  pulseIR(350);
  delayMicroseconds(600);
  pulseIR(350);
  delayMicroseconds(600);
  pulseIR(350);
  delayMicroseconds(1550);
  pulseIR(300);
  delayMicroseconds(650);
  pulseIR(300);
  delayMicroseconds(650);
  pulseIR(300);
  delayMicroseconds(1550);
  pulseIR(350);
  delayMicroseconds(1550);
  pulseIR(300);
  delayMicroseconds(650);
  pulseIR(300);
}

void B_turnright() {
  Serial.println("Sending B_turnright IR signal");
  pulseIR(1850);
  delayMicroseconds(550);
  pulseIR(1850);
  delayMicroseconds(1000);
  pulseIR(300);
  delayMicroseconds(650);
  pulseIR(300);
  delayMicroseconds(650);
  pulseIR(300);
  delayMicroseconds(1550);
  pulseIR(350);
  delayMicroseconds(600);
  pulseIR(350);
  delayMicroseconds(1550);
  pulseIR(350);
  delayMicroseconds(1550);
  pulseIR(300);
  delayMicroseconds(1550);
  pulseIR(350);
  delayMicroseconds(600);
  pulseIR(350);
  delayMicroseconds(1550);
  pulseIR(350);
  delayMicroseconds(600);
  pulseIR(350);
}




#include <NewPing.h>

#define TRIGGER_PIN  5  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     4  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 80 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

const int FORWARD = 0;
const int BACKWARD = 1;
const int LEFT = 2;
const int RIGHT = 3; 

int IRledPin =  3;
int no_object_detected_counter = 0;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup()   {
  pinMode(IRledPin, OUTPUT);       
  Serial.begin(9600);
}

void loop()                     
{
  delay(2000);
  int distance = check_distance();
  Serial.print("Ping: ");
  Serial.print(distance); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
  Serial.println("cm");
  if (distance == 0) {
    if (no_object_detected_counter == 7) {
      Serial.println("Found nothing so spin around looking.");
      Serial.println("Sending IR signal");
      no_object_detected_counter = 0;
      circle();
      spin(RIGHT);
    }
    else {
    Serial.println("No reading...do nothing!");
    }  
    delay(15);
  }
  else if (distance < 15) {
    no_object_detected_counter = 0;
    Serial.println("Too close...going backwards a bit");
    Serial.println("Sending IR signal");
    move(BACKWARD,15);
    delay(15);
  }
  else
  {
    no_object_detected_counter = 0;
    Serial.println("Moving forward...");
    Serial.println("Sending IR signal");
    move(FORWARD,10);
    delay(15);
  }  
  no_object_detected_counter++;
  
//  circle();
//  spin(RIGHT);
//  move(FORWARD,10);
//  move(LEFT,10);
//  move(FORWARD,10);
//  move(BACKWARD,20);
}


int check_distance() {
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  return (uS / US_ROUNDTRIP_CM);
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

void spin(const int d) {
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


void move(const int d, int steps) {
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



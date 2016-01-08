#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>

#define TRIGGER_PIN  19 // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     18  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define TRUE 1

AF_DCMotor motor1(1, MOTOR12_64KHZ); // create motor #1, 64KHz pwm
AF_DCMotor motor2(4, MOTOR12_64KHZ); // create motor #2, 64KHz pwm
int PIR_motion_pin = 14;
int pos = 0;    // variable to store the servo position
int last_pos = 90;
int no_motion_detected_counter = 0;

Servo myservo1;  // create servo object to control servo1 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Initializing!");
  myservo1.attach(9);  // attaches the servo on pin 9 to the servo object 
  motor1.setSpeed(225);     // set the speed to 200/255
  motor2.setSpeed(225);
  myservo1.write(90);               // tell servo to go to position 90 to start
}

void loop() {
  delay(2000);
  Serial.println("Start program");
  while (TRUE) {
    if (digitalRead(PIR_motion_pin) == TRUE && last_pos==90) {
      no_motion_detected_counter = 0;
      unsigned int uS = sonar.ping();
      Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
      Serial.println("cm");
      if ((uS / US_ROUNDTRIP_CM) == 0) {
        continue;
      }
      if ((uS / US_ROUNDTRIP_CM) < 40) {
        Serial.println("Too close...going backwards a bit");
        motor1.run(BACKWARD);      // turn it on going backward
        motor2.run(BACKWARD);
        delay(2000);
        Serial.println("Stopping...");
        motor1.run(RELEASE);      // stopped
        motor2.run(RELEASE);
        delay(3000);
        continue;
      }
      Serial.println("Going forward...");
      motor1.run(FORWARD);      // turn it on going forward
      motor2.run(FORWARD);
      delay(2000);
      motor1.run(RELEASE);      // stopped
      motor2.run(RELEASE);
      delay(1000);  
    }
    if (digitalRead(PIR_motion_pin) == TRUE && last_pos==0) {
      no_motion_detected_counter = 0;
      Serial.println("Going right...");
      motor2.run(BACKWARD);      // turn it on going right
      delay(1000);
      Serial.println("Stopping..");
      motor2.run(RELEASE);      // stopped
      for(pos = 0; pos < 90; pos += 1) {  // goes from 0 degrees to 90 degrees in steps of 1 degree
        myservo1.write(pos);
        delay(15);
      }
      last_pos = 90;
      delay(1000);
    }
    if (digitalRead(PIR_motion_pin) == TRUE && last_pos==180) {
      no_motion_detected_counter = 0;
      Serial.println("Going left...");
      motor1.run(BACKWARD);      // turn it on going left
      delay(1000);
      Serial.println("Stopping...");
      motor1.run(RELEASE);      // stopped
      for(pos = 180; pos >= 90; pos -= 1) {  // goes from 180 degrees to 90 degrees in steps of 1 degree
        myservo1.write(pos);
        delay(15);
      }
      last_pos = 90;
      delay(1000);
    }
    
    no_motion_detected_counter++;
    if (no_motion_detected_counter == 100 && last_pos==0) {
      no_motion_detected_counter = 0;
      for(pos = 0; pos < 90; pos += 1) {  // goes from 0 degrees to 90 degrees in steps of 1 degree
        myservo1.write(pos);
        delay(15);
      }
      last_pos = 90;
      delay(5000);
    }
    if (no_motion_detected_counter == 100 && last_pos==90) {
      no_motion_detected_counter = 0;
      for(pos = 90; pos < 180; pos += 1) {  // goes from 90 degrees to 180 degrees in steps of 1 degree
        myservo1.write(pos);
        delay(15);
      }
      last_pos = 180;
      delay(5000);
    }
    if (no_motion_detected_counter == 100 && last_pos==180) {
      no_motion_detected_counter = 0;
      for(pos = 180; pos >= 1; pos -= 1) {  // goes from 180 degrees to 0 degrees in steps of 1 degree
        myservo1.write(pos);
        delay(15);
      }
      last_pos = 0;
      delay(5000);
    } 
    delay(15);
    Serial.println("Repeating loop...");
  }
}

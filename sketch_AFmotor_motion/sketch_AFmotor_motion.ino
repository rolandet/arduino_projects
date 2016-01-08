#include <AFMotor.h>
#include <NewPing.h>

#define TRIGGER_PIN  19 // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     18  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define TRUE 1

AF_DCMotor motor1(1, MOTOR12_64KHZ); // create motor #1, 64KHz pwm
AF_DCMotor motor2(4, MOTOR12_64KHZ); // create motor #2, 64KHz pwm
int PIR_motion_pin = 14;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor motion test!");
  
  motor1.setSpeed(200);     // set the speed to 200/255
  motor2.setSpeed(200);
}

void loop() {
  Serial.println("Start program");
  while (TRUE) {
    if (digitalRead(PIR_motion_pin) == TRUE) {
      unsigned int uS = sonar.ping();
      Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
      Serial.println("cm");
      if ((uS / US_ROUNDTRIP_CM) == 0) {
        continue;
      }
      if ((uS / US_ROUNDTRIP_CM) < 30) {
        Serial.println("Too close...going backwards a bit");
        motor1.run(BACKWARD);      // turn it on going backward
        motor2.run(BACKWARD);
        delay(1000);
        Serial.println("Stopping...");
        motor1.run(RELEASE);      // stopped
        motor2.run(RELEASE);
        continue;
      }
      Serial.println("Going forward...");
      motor1.run(FORWARD);      // turn it on going forward
      motor2.run(FORWARD);
      delay(2000);
    }
    Serial.println("Stopping...");
    motor1.run(RELEASE);      // stopped
    motor2.run(RELEASE);
    delay(1000);  
  }
}

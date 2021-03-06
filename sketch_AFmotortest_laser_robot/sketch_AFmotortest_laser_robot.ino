#include <AFMotor.h>

AF_DCMotor motor1(1, MOTOR12_64KHZ); // create motor #1, 64KHz pwm
AF_DCMotor motor2(2, MOTOR12_64KHZ); // create motor #2, 64KHz pwm

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");
  
  motor1.setSpeed(255);     // set the speed to 200/255
  motor2.setSpeed(255);
}

void loop() {
  Serial.print("tick");
  
  motor1.run(FORWARD);      // turn it on going forward
  motor2.run(FORWARD);
  delay(10000);

 /* Serial.print("tock");
  motor.run(BACKWARD);     // the other way
  delay(1000);
*/  
  Serial.print("tack");
  motor1.run(RELEASE);      // stopped
  motor2.run(RELEASE);
  
  motor1.run(BACKWARD);      // turn it on going forward
  delay(10000);
  motor1.run(RELEASE);
  delay(1000);
  
  motor1.run(FORWARD);      // turn it on going forward
  motor2.run(FORWARD);
  delay(10000);

 /* Serial.print("tock");
  motor.run(BACKWARD);     // the other way
  delay(1000);
*/  
  Serial.print("tack");
  motor1.run(RELEASE);      // stopped
  motor2.run(RELEASE);
  
  motor2.run(BACKWARD);      // turn it on going forward
  delay(10000);
  motor2.run(RELEASE);
  delay(1000);
}

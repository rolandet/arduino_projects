/* Bluetooth remote controlled robot */

#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>

#define baudRate 57600
#define TRIGGER_PIN  15 // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     14  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

AF_DCMotor motor1(1, MOTOR12_64KHZ); // create motor #1, 64KHz pwm
AF_DCMotor motor2(2, MOTOR12_64KHZ); // create motor #2, 64KHz pwm
int pos = 0;    // variable to store the servo position

Servo myservo1;  // create servo object to control servo1 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

int laserPin = 16;
int x = 0; 
int y = 0;
int xspeed = 0;
int yspeed = 0;
int speed = 0;

signed char data_packet[6];
unsigned char packet_index=0;

void setup()  { 
  
  // use the baud rate your bluetooth module is configured to 
  Serial.begin(baudRate);
  pinMode(laserPin, OUTPUT);
  myservo1.attach(9);  // attaches the servo on pin 9 to the servo object 
  motor1.setSpeed(0);     // set the speed to 0
  motor2.setSpeed(0);
  myservo1.write(180);               // tell servo to go to position 180 to start
    
} 

void loop()  { 
  
  // check if data has been sent from the computer:
  if (Serial.available()) {
    //Serial.println("Available");
    // read the most recent byte:
    data_packet[packet_index] = Serial.read();
    if (packet_index==0)
    {
      Serial.println("Begin...");
    }
    Serial.println(data_packet[packet_index]);
    packet_index++;
    if(packet_index==6 || (data_packet[0]==127 && packet_index==4))
    {
      // full packet received
      process_packet();
    }  
  }
  setMotors();
}

void process_packet()
{
  int lspeed, lturn;
  
  packet_index=0;
  if(data_packet[0]==125)
  {
    x=data_packet[1];
    y=data_packet[2];
    speed=193+(data_packet[3]/2);
    speed = constrain(speed, 193, 255);
    x = constrain(x, -124, 124);
    y = constrain(y, -124, 124);          
  }
  else if(data_packet[0]==127)
  {
    if(data_packet[1]==1)
    {
      for(pos = 180; pos >= 20; pos -= 1) {  // goes from 180 degrees to 135 degrees in steps of 1 degree
        myservo1.write(pos);
      }
      // Shoot the laser
      digitalWrite(laserPin, HIGH); // turns the laser On
      delay(6000);
      digitalWrite(laserPin, LOW);  // turns the laser Off
      for(pos = 20; pos <= 180; pos += 1) {  // goes from 135 degrees to 180 degrees in steps of 1 degree
        myservo1.write(pos);
      }
    }
  }  

}

void setMotors()
{
   if (x == 0 && y == 0)
   {
      motor1.run(RELEASE);      // stopped
      motor2.run(RELEASE);
   }
   //Serial.println("run motor");
   else if (y > 0 && (x > -62 && x < 62))
   {
        //Serial.println(x," ",y," ",speed);
        motor1.setSpeed(speed);
        motor2.setSpeed(speed);
        motor1.run(FORWARD); 
        motor2.run(FORWARD);
   }
   else if (y < 0 && (x > -62 && x < 62)) 
   {
        //Serial.println(x," ",y," ",speed);
        motor1.setSpeed(speed);
        motor2.setSpeed(speed);
        motor1.run(BACKWARD); 
        motor2.run(BACKWARD);
   }
   else if (x < 0 && (y > -62 && y < 62))
   {
        //Serial.println(x," ",y," ",speed);motor1.setSpeed(speed);
        motor1.setSpeed(speed);
        motor2.setSpeed(speed);
        motor1.run(BACKWARD); 
        motor2.run(FORWARD);
   }
   
   else
   {
        //Serial.println(x," ",y," ",speed);motor1.setSpeed(speed);
        motor1.setSpeed(speed);
        motor2.setSpeed(speed);
        motor1.run(FORWARD); 
        motor2.run(BACKWARD);
   } 
  
}

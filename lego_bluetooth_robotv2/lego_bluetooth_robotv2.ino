/* Bluetooth remote controlled robot */

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

#define baudRate 57600

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *motor1 = AFMS.getMotor(1);
// You can also make another motor on port M2
//Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);
Adafruit_DCMotor *motor2 = AFMS.getMotor(2);

int x = 0; 
int y = 0;
int xspeed = 0;
int yspeed = 0;
int speedm1 = 0;
int speedm2 = 0;

signed char data_packet[6];
unsigned char packet_index=0;

void setup()  { 
  
  // use the baud rate your bluetooth module is configured to 
  Serial.begin(baudRate);
  
  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  motor1->setSpeed(0);     // set the speed to 0
  motor2->setSpeed(0);
    
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
    speedm1=193+(data_packet[3]/2);
    speedm1 = constrain(speedm1, 193, 255);
    speedm2=193+(data_packet[3]/2);
    speedm2 = constrain(speedm2, 193, 255);
    x = constrain(x, -124, 124);
    y = constrain(y, -124, 124);          
  }
  else if(data_packet[0]==127)
  {
    if(data_packet[1]==1)
    {
      // Do nothing for now if button 1 is pressed
      }
  }  

}

void setMotors()
{
   if (x == 0 && y == 0)
   {
      motor1->run(RELEASE);      // stopped
      motor2->run(RELEASE);
   }
   //Serial.println("run motor");
   else if (y > 0 && (x > -62 && x < 62))
   {
        //Serial.println(x," ",y," ",speed);
        motor1->setSpeed(speedm1-30);
        motor2->setSpeed(speedm2);
        motor1->run(FORWARD); 
        motor2->run(FORWARD);
   }
   else if (y < 0 && (x > -62 && x < 62)) 
   {
        //Serial.println(x," ",y," ",speed);
        motor1->setSpeed(speedm1);
        motor2->setSpeed(speedm2);
        motor1->run(BACKWARD); 
        motor2->run(BACKWARD);
   }
   else if (x < 0 && (y > -62 && y < 62))
   {
        //Serial.println(x," ",y," ",speed);motor1.setSpeed(speed);
        motor1->setSpeed(speedm1);
        motor2->setSpeed(speedm2);
        motor1->run(BACKWARD); 
        motor2->run(FORWARD);
   }
   
   else
   {
        //Serial.println(x," ",y," ",speed);motor1.setSpeed(speed);
        motor1->setSpeed(speedm1);
        motor2->setSpeed(speedm2);
        motor1->run(FORWARD); 
        motor2->run(BACKWARD);
   } 
  
}

#include<Servo.h>
#include<ros.h>
#include<std_msgs/UInt16.h>
#include <std_msgs/Bool.h>

int contact;

std_msgs::Bool ordreDepart;

ros::NodeHandle nc;

void servo_f(const std_msgs::UInt16& cmd_msg);

ros::Subscriber<std_msgs::UInt16> sub("servo", &servo_f);
ros::Publisher depart("depart", &ordreDepart);

Servo servo1;
Servo servo2;

void servo_f(const std_msgs::UInt16& cmd_msg)
{
   if(cmd_msg.data==0){
        servo1.write(25);
   }
   if(cmd_msg.data==1){
        servo1.write(170);
   }
   if(cmd_msg.data==2){
        servo2.write(50);
   }
   if(cmd_msg.data==3){
        servo2.write(180);
        delay(1000);
        servo2.write(0);
   }
}

void verifierContacteur(){
  if(contact == 0){
    if(analogRead(A15)>600){
      for(int i=0;i<=5;i++){
        if(analogRead(A15)<600){
          i=6;
        }
        if(i==5){
           contact = 1;
           ordreDepart.data = true;
           depart.publish(&ordreDepart);
        }
      }
    }
  }
  if(contact == 1){
    if(analogRead(A15)<100){
      contact = 0;
      ordreDepart.data = false;
      depart.publish(&ordreDepart);
    }
  }
}

void setup(){
  
  //Diode
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  
  //Contacteur
  contact = 0;
  pinMode(A15,INPUT);
  
  nc.initNode();
  nc.advertise(depart);
  
  ordreDepart.data = false;
  
  //Servomoteurs
  Serial.begin(57600);

  servo1.attach(7);
  servo1.write(0);
  servo1.write(0);
  
  servo2.attach(9);
  servo2.write(0);

  nc.subscribe(sub);
}

void loop()
{
  digitalWrite(13,HIGH);
  delay(1000);
//  verifierContacteur();
//  nc.spinOnce();
  delay(1000);
  servo1.write(90);
  digitalWrite(13,LOW);
  delay(1000);
  servo1.write(0);
}

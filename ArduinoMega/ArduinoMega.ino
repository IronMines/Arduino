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

Servo servo;

void servo_f(const std_msgs::UInt16& cmd_msg){
    if(cmd_msg.data >=0 && cmd_msg.data <= 180){
        servo.write(cmd_msg.data);
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
  
  //Contacteur
  contact = 0;
  pinMode(A15,INPUT);
  
  nc.initNode();
  nc.advertise(depart);
  
  ordreDepart.data = false;
  
  //Servomoteurs
  Serial.begin(57600);

  servo.attach(7);
  servo.write(0);
  
  nc.subscribe(sub);
}

void loop()
{
  delay(100);
  verifierContacteur();
  nc.spinOnce();
}

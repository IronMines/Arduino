#include <ros.h>
#include <std_msgs/Bool.h>

int contact;

std_msgs::Bool ordreDepart;

ros::NodeHandle nc;
ros::Publisher depart("depart", &ordreDepart);

void setup() {
  contact = 0;
  pinMode(A15,INPUT);
  pinMode(13,OUTPUT);
  
  nc.initNode();
  nc.advertise(depart);
  
  ordreDepart.data = false;
}

void loop() {
  digitalWrite(13,HIGH);
  ordreDepart.data = false;
  while(contact == 0){
    depart.publish(&ordreDepart);
    nc.spinOnce();
    if(analogRead(A15)>600){
      for(int i=0;i<=5;i++){
        digitalWrite(13,LOW);
        delay(50);
        digitalWrite(13,HIGH);
        delay(100);
        if(analogRead(A15)<600){
          i=6;
        }
        if(i>4){
           contact = 1;
           digitalWrite(13,LOW);
           ordreDepart.data = true;
           depart.publish(&ordreDepart);
           nc.spinOnce();
         }
      }
    }
  }
  while(contact == 1){
    if(analogRead(A15)<100){
      contact = 0;
    }
  }
}

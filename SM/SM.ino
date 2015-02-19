#include<Servo.h>
#include<ros.h>
#include<std_msgs/UInt16.h>

ros::NodeHandle ns;

void servo_f(const std_msgs::UInt16& cmd_msg);

ros::Subscriber<std_msgs::UInt16> sub("servo", &servo_f);

Servo servo1;
Servo servo2;

void servo_f(const std_msgs::UInt16& cmd_msg)
{
   if(cmd_msg.data==0)
   servo1.write(45);
   if(cmd_msg.data==1)
   servo1.write(170);
   if(cmd_msg.data==2)
   servo2.write(50);
   if(cmd_msg.data==3)
   servo2.write(180);
}

void setup(){

  Serial.begin(9600);

  servo1.attach(1);
  servo1.write(0);

  servo2.attach(2);
  servo2.write(0);

  ns.initNode();
  ns.subscribe(sub);

}

void loop()
{
    ns.spinOnce();
    delay(1);
}

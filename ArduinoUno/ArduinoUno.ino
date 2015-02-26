#include <LinkedList.h>
#include <ros.h>
#include <std_msgs/UInt16.h>

int clock = 0;

ros::NodeHandle nc;

std_msgs::UInt16 aSonar;

ros::Publisher sonar0("sonar0", &aSonar);
ros::Publisher sonar1("sonar1", &aSonar);
ros::Publisher sonar2("sonar2", &aSonar);
ros::Publisher sonar3("sonar3", &aSonar);
//ros::Publisher sonar4("sonar4", &aSonar);

LinkedList<ros::Publisher*> sonars;

void checkAllSonars()
{
   for(int i = 0 ; i < min(sonars.size(), 3) ; i++)
    {
      aSonar.data = readSonar(11-i);
      sonars.get(i)->publish(&aSonar);
    }
  if (sonars.size() >= 4) {
    aSonar.data = readSonar(6);
    sonars.get(3)->publish(&aSonar);
    if (sonars.size() == 5) {
      aSonar.data = readSonar(5);
      sonars.get(4)->publish(&aSonar);
    }
  }
}

long readSonar(int pingPin)
{
  long duration;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH, 20000);
  
  return microsecondsToMilimeters(duration);
}


long microsecondsToMilimeters(long microseconds)
{
  return microseconds * 10 / 29 / 2;
}


void setup()
{
  nc.initNode();
  //On doit declarer chaque publisher au pres de ROS
  sonars = LinkedList<ros::Publisher*>();
  
  sonars.add(&sonar0);
  sonars.add(&sonar1);
  sonars.add(&sonar2);
  sonars.add(&sonar3);
  //sonars.add(&sonar4);
  
  for(int i = 0 ; i < sonars.size() ; i++)
  {
    nc.advertise(*sonars.get(i));
  }
  
  //On initialise les messages
  aSonar.data = 0;
}

void loop()
{
  checkAllSonars();
  nc.spinOnce();
  
  delay(1);
}

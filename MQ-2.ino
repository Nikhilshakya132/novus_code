#include <ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int16.h>
#include <geometry_msgs/Point.h>

#define pin_mq2 A0
#define RO_CLEAN_AIR_FACTOR (9.21)//RO_CLEAR_AIR_FACTOR=(Sensor resistance in clean ai
float RO=10;// initial resistance value
ros::NodeHandle nh;
geometry_msgs::Point mq2_msg; 
ros::Publisher chatter5("Gas_SENSOR", &mq2_msg);
void setup()
{ 
  
  nh.initNode();
 
   nh.advertise(chatter5);

}
void loop()
{
 float mq2=analogRead(pin_mq2);
  /*
    Exponential regression:
    Gas    | a      | b
    H2     | 987.99 | -2.162
    LPG    | 574.25 | -2.222
    CO     | 36974  | -3.109
    Alcohol| 3616.1 | -2.675
    Propane| 658.71 | -2.168
  */
  //_PPM =  a*ratio^b
   mq2= (mq2 * (5.0 / 1023.0));
   float mq2_rs = ((5.0 * 10.0) / mq2) - 10.0;
   float ratio_mq2 = mq2_rs/RO;
   float LPG = 574.25*pow(ratio_mq2,-2.222);
   float alcohol = 3616.1*pow(ratio_mq2,-2.675);
   float propanol = 658.71*pow(ratio_mq2,-2.168);
mq2_msg.x = LPG;
  mq2_msg.y = alcohol;
  mq2_msg.z = propanol;
  chatter5.publish(&mq2_msg);
  nh.spinOnce();
delay(500);
}

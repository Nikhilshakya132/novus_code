#include<ros.h>
#include<std_msgs/Float32.h>
ros::NodeHandle  nh;
std_msgs::Float32 uv_msg;
ros::Publisher chatter9("uvsensor", &uv_msg);
void setup() 
{
  nh.initNode();
  nh.advertise(chatter9);
  Serial.begin(9600);
}
 
void loop() 
{
  
  float sensorVoltage; 
  float sensorValue;
 
  sensorValue = analogRead(A0);
  sensorVoltage = sensorValue/1024*3.3;
  Serial.print("sensor reading = ");
  Serial.print(sensorValue);
  Serial.println("");
  Serial.print("sensor voltage = ");
  Serial.print(sensorVoltage);
  Serial.println(" V");
  chatter9.publish(&uv_msg);
  nh.spinOnce();
  delay(1000);
}

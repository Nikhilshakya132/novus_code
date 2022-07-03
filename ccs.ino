#include<ros.h>
#include<std_msgs/Float32.h>
ros::NodeHandle  nh;
#include "Adafruit_CCS811.h"
std_msgs::Float32 ccs_msg;
ros::Publisher chatter("ccs811", &ccs_msg);
Adafruit_CCS811 ccs;
void setup() {
  nh.initNode();
  nh.advertise(chatter);
Serial.begin(9600);
Serial.println("CCS811 test");
if(!ccs.begin()){
Serial.println("Failed to start sensor! Please check your wiring.");
while(1);
}
//calibrate temperature sensor
while(!ccs.available());
float temp = ccs.calculateTemperature();
ccs.setTempOffset(temp - 25.0);
}
void loop() {
if(ccs.available()){
float temp = ccs.calculateTemperature();
if(!ccs.readData()){
  ccs_msg.data = temp;
  chatter.publish( &ccs_msg );
  
/*Serial.print("CO2: ");
Serial.print(ccs.geteCO2());
Serial.print("ppm, TVOC: ");
Serial.print(ccs.getTVOC());
Serial.print("ppb Temp:");
Serial.println(temp);
*/
}
else{
Serial.println("ERROR!");
while(1);
}
}
nh.spinOnce();
delay(500);
}

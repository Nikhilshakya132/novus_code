#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <ros.h>
#include <geometry_msgs/Point.h>

int RXPin = 3;
int TXPin = 2;
int GPSBaud = 9600;
ros::NodeHandle nh;
geometry_msgs::Point gps_msg; 
ros::Publisher chatter("GPS", &gps_msg);

TinyGPSPlus gps;
SoftwareSerial gpsSerial(RXPin, TXPin);

void setup()
{  
  gpsSerial.begin(GPSBaud);
  nh.getHardware()->setBaud(9600);
  nh.initNode();
  nh.advertise(chatter);
}

void loop()
{
  while (gpsSerial.available() > 0)
    if (gps.encode(gpsSerial.read()))
    {
        if (gps.location.isValid())
        {
             float Latitude = (gps.location.lat(), 6);
    
             float Longitude = (gps.location.lng(), 6);
    
             float Altitude = (gps.altitude.meters());
             gps_msg.x = Latitude;
             gps_msg.y = Longitude;
             gps_msg.z =Altitude ;
        }
     }

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    while(true);
  }
  chatter.publish(&gps_msg);
  nh.spinOnce();
  delay(1000);
}

/*------------------------------------------------------------------------------

  Driver code is based on Garmin LIDAR-Lite v3hp Arduino Library (https://github.com/garmin/LIDARLite_Arduino_Library) 
  Setup Documentation Hardware: https://support.garmin.com/en-US/?partNumber=010-01722-00&tab=manuals
  Setup Documentation Software: https://github.com/garmin/LIDARLite_Arduino_Library
  Default Address:  0x62.

 
 * Copyright (C) 2019-2021 LEIDOS.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 
------------------------------------------------------------------------------*/
#include <LIDARLite.h>
#include <Wire.h>
#include <ros.h>
#include <ros/time.h>
#include <sensor_msgs/Range.h>
//LIDARLite object
LIDARLite lidarv3hp;
//ROS node handle
ros::NodeHandle  n;
//Message type sensor_msgs::Range
sensor_msgs::Range distance_msg;
//ROS Publisher object
ros::Publisher pub_distance( "range_sensor2/range", &distance_msg);
char frameid[] = "/laser_lite_v3hp_sensor2";

void setup()
{
  //Serial communication BaudRate:115200
  Serial.begin(115200); 
  // begin(int configuration, bool fasti2c, char lidarliteAddress)
  // 0 sets configuration to default and true sets I2C to 400 kHz
  // If using long wire reduce this speed
  lidarv3hp.begin(0, true); 
  // Various configuration of lidar_lite_v3hp
  // 0-> Balanced performance 1-> Short range and high speed 2-> Default range and higher speed 
  // 3-> Maximum range 4-> High sensitivity detection 5-> Low sensitivity detection
  lidarv3hp.configure(0);
  // ROS initialization
  n.initNode();
  n.advertise(pub_distance);
  // ROS Message initialization
  //radiation_type
  distance_msg.radiation_type = sensor_msgs::Range::INFRARED;
  //frame_id
  distance_msg.header.frame_id =  frameid;
  //max_range
  distance_msg.max_range = 40.0;
  //min_range
  distance_msg.min_range = 0.01;
  //field_of_view
  distance_msg.field_of_view = 0.001;
  
}

void loop()
{
  //Current timestamp 
  distance_msg.header.stamp = n.now();
  //Extract distance 
  distance_msg.range = lidarv3hp.distance()/100.0;
  //Publish distance to topic sensor2_data
  pub_distance.publish(&distance_msg);
  n.spinOnce(); 
  delay(10); 
}

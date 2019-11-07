/*
 * Copyright (C) 2019 LEIDOS.
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
 */
#include <ros/ros.h>
#include <sensor_msgs/Range.h>
#include <std_msgs/Float64.h>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <math.h> 
#include <cav_msgs/SystemAlert.h>
#include <cav_msgs/DriverStatus.h>
// using namespace message_filters;

class LidarLiteNode
{

 private:
  
  message_filters::Subscriber<sensor_msgs::Range> sub_1_;
  message_filters::Subscriber<sensor_msgs::Range> sub_2_;
  ros::Publisher pub_ang_;
  ros::Subscriber sub_alert_;
  ros::Time last_update_time_;
  //ros::Timer timer_;
  // timer_ = node.createTimer(ros::Duration(1.0), &NovatelGpsNodelet::publish_status,this);
  uint8_t status_lidar_;
  

  typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::Range, sensor_msgs::Range> MySyncPolicy;
  typedef message_filters::Synchronizer<MySyncPolicy> Sync;
  boost::shared_ptr<Sync> sync_;
 public:
  LidarLiteNode(ros::NodeHandle *nh);
 
  void callback(const sensor_msgs::RangeConstPtr &in1, const sensor_msgs::RangeConstPtr &in2);

  void alertCallback(const cav_msgs::SystemAlertConstPtr &msg);

/*void updateLidarStatus();*/

 cav_msgs::DriverStatus status_;
 ros::Publisher pub_status_;
 

};


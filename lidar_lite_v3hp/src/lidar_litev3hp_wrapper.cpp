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
#include "lidar_litev3hp_wrapper.h"

LidarLiteNode::LidarLiteNode(ros::NodeHandle *nh)
  {
    status_.lidar_lite_v3hp= true;
    sub_1_.subscribe(*nh, "sensor1_data", 1);
    sub_2_.subscribe(*nh, "sensor2_data", 1);
    sync_.reset(new Sync(MySyncPolicy(10), sub_1_, sub_2_));
    sync_->registerCallback(boost::bind(&LidarLiteNode::callback, this, _1, _2));
    pub_ang_=nh->advertise<std_msgs::Float64>("trailer_angle",10);
    sub_alert_=nh->subscribe("system_alert",10,&LidarLiteNode::alertCallback,this);
    pub_status_=nh->advertise<cav_msgs::DriverStatus>("driver_discovery", 10);
  }

   void LidarLiteNode::callback(const sensor_msgs::RangeConstPtr &in1, const sensor_msgs::RangeConstPtr &in2)
  {
    ROS_INFO_STREAM("sensor1= "<<in1->range<<" "<<"sensor2= "<<in2->range);
    status_lidar_=cav_msgs::DriverStatus::OPERATIONAL;

    if(status_lidar_==cav_msgs::DriverStatus::OPERATIONAL)
    {
      status_.status=cav_msgs::DriverStatus::OPERATIONAL;
      last_update_time_=ros::Time::now();
    }

    double sensor_distance; //Distance between sensor
    nh->getParam("/distance_between_two_sensor",sensor_distance);
    
    double opposite_side=((in1->range)-(in2->range));

    double hypotenuse=hypot(sensor_distance,opposite_side);

    double ang_deg=asin(opposite_side/hypotenuse);

    std_msgs::Float64 msg_ang;
    msg_ang.data=ang_deg*0.01745329252;

   pub_ang_.publish(msg_ang);
   pub_status_.publish(status_);
  }

    void LidarLiteNode::alertCallback(const cav_msgs::SystemAlertConstPtr &msg)
{
  if( msg->type==cav_msgs::SystemAlert::FATAL || msg->type==cav_msgs::SystemAlert::SHUTDOWN)
    {
     ros::shutdown();
    }
}

/*void updateLidarStatus()
{
    ros::Duration lidar_time_difference=ros::Time::now()-last_update_time_;
    //Greater than 2 seconds of non-response is the minimum time required to classify as not connected
  if (last_update_time_.isZero() || (lidar_time_difference>ros::Duration(2.0)) && status_lidar_==cav_msgs::DriverStatus::OPERATIONAL)
    {
    status_lidar_=cav_msgs::DriverStatus::OFF;
    }
}*/
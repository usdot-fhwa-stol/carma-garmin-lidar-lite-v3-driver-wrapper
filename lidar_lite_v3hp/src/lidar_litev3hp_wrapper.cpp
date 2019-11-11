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

LidarLiteNode::LidarLiteNode()
  {
    status_.trailer_angle_sensor= false;
    timer_ = nh_.createTimer(ros::Duration(1.0), &LidarLiteNode::updateLidarStatus,this);
    sub_1_.subscribe(nh_, "range_sensor1/range", 1);
    sub_2_.subscribe(nh_, "range_sensor2/range", 1);
    sync_.reset(new Sync(MySyncPolicy(10), sub_1_, sub_2_));
    sync_->registerCallback(boost::bind(&LidarLiteNode::sensorCallback, this, _1, _2));
    pub_ang_=nh_.advertise<std_msgs::Float64>("trailer_angle",10);
    sub_alert_=nh_.subscribe("system_alert",10,&LidarLiteNode::alertCallback,this);
    pub_status_=nh_.advertise<cav_msgs::DriverStatus>("driver_discovery", 10);
  }

   void LidarLiteNode::sensorCallback(const sensor_msgs::RangeConstPtr &sensor_inp1, const sensor_msgs::RangeConstPtr &sensor_inp2)
  {
    status_.trailer_angle_sensor= true;
    status_.status=cav_msgs::DriverStatus::OPERATIONAL;
    last_update_time_=ros::Time::now();
   
    double sensor_distance; //Distance between sensor
    nh_.getParam("~/distance_between_two_sensor",sensor_distance);
    ROS_INFO_STREAM("sensor1= "<<sensor_inp1->range<<" "<<"sensor2= "<<sensor_inp2->range<<"sensor_distance= "<<sensor_distance);
    std_msgs::Float64 msg_ang;
    msg_ang.data=worker_.LidarLiteNodeWorker::trailerAngle(sensor_distance,sensor_inp1->range,sensor_inp2->range);
    pub_ang_.publish(msg_ang);
   
  }

    void LidarLiteNode::alertCallback(const cav_msgs::SystemAlertConstPtr &msg)
{
  if( msg->type==cav_msgs::SystemAlert::FATAL || msg->type==cav_msgs::SystemAlert::SHUTDOWN)
    {
     ros::shutdown();
    }
}

void LidarLiteNode::updateLidarStatus(const ros::TimerEvent& )
{
    ros::Duration lidar_time_difference=ros::Time::now()-last_update_time_;
    //Greater than 2 seconds of non-response is the minimum time required to classify as not connected
  if (last_update_time_.isZero() || (lidar_time_difference>ros::Duration(2.0)))
    {
    status_.status=cav_msgs::DriverStatus::OFF;
    status_.trailer_angle_sensor= false;
    }
    pub_status_.publish(status_);
}
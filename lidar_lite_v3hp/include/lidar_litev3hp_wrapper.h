/*
 * Copyright (C) 2019-2020 LEIDOS.
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

#ifndef LIDAR_LITEV3HP_WRAPPER_H
#define LIDAR_LITEV3HP_WRAPPER_H

#include <ros/ros.h>
#include <sensor_msgs/Range.h>
#include <std_msgs/Float64.h>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <cav_msgs/SystemAlert.h>
#include <cav_msgs/DriverStatus.h>
#include "lidar_litev3hp_worker.h"

class LidarLiteNode
{

 private:
  cav_msgs::DriverStatus status_;
  message_filters::Subscriber<sensor_msgs::Range> sub_1_;
  message_filters::Subscriber<sensor_msgs::Range> sub_2_;
  ros::Publisher pub_ang_;
  ros::Subscriber sub_alert_;
  ros::Time last_update_time_;
  ros::Timer timer_;
  uint8_t status_lidar_;
  ros::NodeHandle nh_;
  ros::NodeHandle pnh_;
  ros::Publisher pub_status_;
  typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::Range, sensor_msgs::Range> MySyncPolicy;
  typedef message_filters::Synchronizer<MySyncPolicy> Sync;
  boost::shared_ptr<Sync> sync_;
  LidarLiteNodeWorker worker_;
 public:
   /*! \fn LidarLiteNode()
    \brief LidarLiteNode constructor to initialize all the ros publisher,subscriber object and other parameters.
   */
  LidarLiteNode();
    /*! \fn sensorCallback(const sensor_msgs::RangeConstPtr &sensor_inp1, const sensor_msgs::RangeConstPtr &sensor_inp2)
    \brief sensorCallback function extract sensor_inp1 and sensor_inp2 from respective topics.
    \param sensor_distance The fixed distance between two sensors.
    \param sensor_inp1 The input value of sensor1.
    \param sensor_inp2 The input value of sensor2.
    */
  void sensorCallback(const sensor_msgs::RangeConstPtr &sensor_inp1, const sensor_msgs::RangeConstPtr &sensor_inp2);
   /*! \fn alertCallback(const cav_msgs::SystemAlertConstPtr &msg)
    \brief alertCallback function monitors for any SystemAlert sent and shuts ros down.
    \param msg The data received from SystemAlert topic.
   */
  void alertCallback(const cav_msgs::SystemAlertConstPtr &msg);
   /*! \fn updateLidarStatus(const ros::TimerEvent&)
    \brief updateLidarStatus is a timer function to publish lidar status to DriverDiscovery.
   */
  void updateLidarStatus(const ros::TimerEvent&);
 
};

#endif /* LIDAR_LITEV3HP_WRAPPER_H */
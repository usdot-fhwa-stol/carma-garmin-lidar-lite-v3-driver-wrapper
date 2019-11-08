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

#ifndef LIDAR_LITEV3HP_WORKER_H
#define LIDAR_LITEV3HP_WORKER_H

#include <math.h> 

class LidarLiteNodeWorker
{

 public:
 	    /*! \fn trailerAngle(double sensor_distance,double sensor_inp1,double sensor_inp2)
    \brief trailerAngle function uses sensor_distance and two sensor input to calculate trailer angle.
    \param sensor_distance The fixed distance between two sensors.
    \param sensor_inp1 The input value of sensor1.
    \param sensor_inp2 The input value of sensor2.
    */
  double trailerAngle(double sensor_distance,double sensor_inp1,double sensor_inp2);
 
};

#endif /* LIDAR_LITEV3HP_WORKER_H */
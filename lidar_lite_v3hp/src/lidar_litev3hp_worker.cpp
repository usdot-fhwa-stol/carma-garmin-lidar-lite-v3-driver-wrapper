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
#include "lidar_litev3hp_worker.h"

double LidarLiteNodeWorker::trailerAngle(double sensor_distance,double sensor_inp1,double sensor_inp2)
{
	double opposite_side=((sensor_inp1)-(sensor_inp2));

    double hypotenuse=hypot(sensor_distance,opposite_side);

    double ang_rad=asin(opposite_side/hypotenuse);

    return(ang_rad);
}
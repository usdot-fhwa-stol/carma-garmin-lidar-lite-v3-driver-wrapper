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
#include "lidar_litev3hp_worker.h"

// The trailer angle math involves solving right angle triangle with trigonometry equations.

double LidarLiteNodeWorker::trailerAngle(double sensor_distance,double sensor_inp1,double sensor_inp2)
{	
	//The opposite side of the triangle is found from the difference of both input sensor distance.
	double opposite_side=((sensor_inp1*100.0)-(sensor_inp2*100.0));
    // The hypotenuse is found using the opposite_side and adjacent side(here sensor_distance).
    double hypotenuse=hypot(sensor_distance,opposite_side);
    //Trailer angle in radians is the sin inverse of opposite_side divided by hypotenuse.
    double ang_rad=asin(opposite_side/hypotenuse);

    return(ang_rad);
}
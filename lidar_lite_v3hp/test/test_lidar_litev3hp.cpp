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
#include <gtest/gtest.h>

TEST(LidarLiteV3hpWorkerTest, testTrailerAngleNormalState)
{
    LidarLiteNodeWorker worker;
    double sensor_distance=100;//Fixed sensor distance at 100 cm
    double sensor_inp1=150;// sensor input one
    double sensor_inp2=150;// sensor input two

    EXPECT_NEAR(worker.trailerAngle(sensor_distance,sensor_inp1,sensor_inp2),0);
}

TEST(LidarLiteV3hpWorkerTest, testTrailerAngleLeftTurn)
{
    LidarLiteNodeWorker worker;
    double sensor_distance=100;//Fixed sensor distance at 100 cm
    double sensor_inp1=150;// sensor input one
    double sensor_inp2=100;// sensor input two

    EXPECT_NEAR(worker.trailerAngle(sensor_distance,sensor_inp1,sensor_inp2),0.463648);
}

TEST(LidarLiteV3hpWorkerTest, testTrailerAngleRightTurn)
{
    LidarLiteNodeWorker worker;
    double sensor_distance=100;//Fixed sensor distance at 100 cm
    double sensor_inp1=100;// sensor input one
    double sensor_inp2=150;// sensor input two

    EXPECT_NEAR(worker.trailerAngle(sensor_distance,sensor_inp1,sensor_inp2),-0.463648);
}

TEST(LidarLiteV3hpWorkerTest, testTrailerAngleLeftTurn)
{
    LidarLiteNodeWorker worker;
    double sensor_distance=100;//Fixed sensor distance at 100 cm
    double sensor_inp1=150;// sensor input one
    double sensor_inp2=100;// sensor input two

    EXPECT_NEAR(worker.trailerAngle(sensor_distance,sensor_inp1,sensor_inp2),0.785398);
}

TEST(LidarLiteV3hpWorkerTest, testTrailerAngleRightTurn)
{
    LidarLiteNodeWorker worker;
    double sensor_distance=100;//Fixed sensor distance at 100 cm
    double sensor_inp1=110;// sensor input one
    double sensor_inp2=210;// sensor input two

    EXPECT_NEAR(worker.trailerAngle(sensor_distance,sensor_inp1,sensor_inp2),-0.785398);
}

// Run all the tests
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
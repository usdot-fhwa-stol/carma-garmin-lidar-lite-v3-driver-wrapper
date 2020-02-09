

Instruction for setting up the Arduino (Use Arduino Uno or Higher ) and package.

1) Wire the lidar lite v3 hp according to Setup Documentation Hardware: https://support.garmin.com/en-US/?partNumber=010-01722-00&tab=manuals

2) Following library needs to be installed in the Arduino Library folder

a) garmin/LIDARLite_Arduino_Library
https://github.com/garmin/LIDARLite_Arduino_Library

b)rosserial_arduino
http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup
Note: Its better to use the rosserial from source over binary and do catkin_make install as this make sure everything is installed over just catkin_make

2) Load the Arduino code and build it. Note sensor 1 code should be put in one Arduion and the other Arduino with sensor 2 code.

3) Clone the CARMAMsgs repo into the src : https://github.com/usdot-fhwa-stol/CARMAMsgs.git.

4) Connect both the Arduino controllers and check the ports using following

a) ls -l /dev/ttyACM* and make sure /dev/ttyACM0 and /dev/ttyACM0 showsup.

b) chmod 777 /dev/ttyACM0 and chmod 777 /dev/ttyACM1 to give port access to Arduino serial channel.

5) Make sure to check the launch file and adjust the parameters as needed. The distance between the sensors mounted are currently set to 150 cm. Change this as per the mount requirement and update the configuration file. Its adviced to use distance of above 100 cm to avoid senor to sensor reflectivity interference.

Note: Please use 100kHz I2C speed if using I2C wire length above 25 cm.






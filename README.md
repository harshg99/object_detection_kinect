# Object Detection and 3D Position detection with Kinect
## Introduction 

Industrial robots are widely used in assembly tasks in various industries. In order to perform these tasks accurately, it is important to have a system in place that can recognize the objects that need to be assembled. One way to do this is through the use of computer vision techniques, such as using a Kinect V2 sensor to identify the location of objects. The Kinect V2 is a depth sensor that uses infrared lasers and a structured light system to create a 3D map of the environment. By analyzing this map, it is possible to determine the location and orientation of objects within the environment.

In addition to object recognition, it is also important to be able to correct for any misalignments between the objects that need to be assembled. This can be done using force torque sensing, which involves using sensors to measure the forces and torques acting on an object. By analyzing these forces and torques, it is possible to determine the position and orientation of the object, and make any necessary corrections to align it with the target object.

Computer vision and force torque sensing can help industrial robots to perform assembly tasks more accurately and efficiently, resulting in improved productivity and quality in manufacturing environments.

## Devices used

1. Microsoft Kinect
2. Kuka LBR -IIWA Robotic Arm
3. ATI force sensors
4. Robotiq Gripper S170

## Architecture
![image](https://user-images.githubusercontent.com/28558013/208742854-f19dffff-f71f-480d-8974-a5a07e6810cd.png)

## Usage

1. Train the model to identify objects and targets based on their QR codes
2. Startup kinect drivers
3. Complie Main.cpp and execute main.cpp to obtain the target detection coordinates
4. Execute UDP server to communicate the object positions locations with the robot
5. Execute obnboard robot controller to move towards object to assemble and object to dock it with.

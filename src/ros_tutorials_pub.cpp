#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sstream>
#include "studypkg/tutorial_msg.h"
int main(int argc, char **argv)
{
  ros::init(argc, argv, "ros_tutorials_pub");
  ros::NodeHandle nh;
  ros::Publisher ros_tutorial_p = nh.advertise<studypkg::tutorial_msg>("ros_tutorial_msg", 100);

  ros::Rate loop_rate(10);

  while(ros::ok())
  {
    std_msgs::String msg;
    studypkg::tutorial_msg c_msg;
    c_msg.stamp = ros::Time::now();
    c_msg.num = rand() % 10;

    ROS_INFO("Publish Custom msg.num (0 to 9) : %d",c_msg.num);
    ROS_INFO("Publish CUstom msg.stamp.sec : %d",c_msg.stamp.sec);

    ros_tutorial_p.publish(c_msg);
    loop_rate.sleep();
  }
  return 0;
}

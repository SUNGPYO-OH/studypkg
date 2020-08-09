#include "ros/ros.h"
#include "std_msgs/String.h"
#include "studypkg/tutorial.h"

void chatterCallback(const studypkg::tutorial::ConstPtr& msg)
{
  ROS_INFO("receive message = %d",msg->stamp.sec);
  ROS_INFO("receive message = %d",msg->num);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "ros_tutorials_sub");
  ros::NodeHandle nh;

  ros::Subscriber sub = nh.subscribe("ros_tutorial_msg", 100, chatterCallback);

  ros::spin();

  return 0;
}

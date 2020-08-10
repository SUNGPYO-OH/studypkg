#include "ros/ros.h"
#include "studypkg/tutorial_srv.h"

bool add(studypkg::tutorial_srv::Request &req,
         studypkg::tutorial_srv::Response &res)
{
  res.result = req.a + req.b;
  ROS_INFO("request: x=%ld, y=%ld", (long int)req.a, (long int)req.b);
  ROS_INFO("sending back response: [%ld]", (long int)res.result);
  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "rostutorials_server");
  ros::NodeHandle nh;

  ros::ServiceServer service = nh.advertiseService("ros_tutorial_srv", add);
  ROS_INFO("Ready to add two ints.");
  ros::spin();

  return 0;
}

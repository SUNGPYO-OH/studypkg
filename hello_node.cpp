#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sstream>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "hellonode"); //initialization
  ros::NodeHandle nh;
  ros::Publisher chatter_pub = nh.advertise<std_msgs::String>("HELLO_TOPIC",1000); //topic_name
	ros::Rate loop_rate(10);
  int countnum=0;

	while(ros::ok())
	{
		std_msgs::String msg;
		std::stringstream ss;
    		ss << "hello" << countnum;
		msg.data = ss.str();
		ROS_INFO("%s", msg.data.c_str());
		chatter_pub.publish(msg);
		ros::spinOnce();
		loop_rate.sleep();
  		countnum+=1;
	}
	return 0;
}

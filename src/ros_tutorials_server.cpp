#include "ros/ros.h"
#include "studypkg/tutorial_srv.h"

// PARAMETER SET
#define PLUS 1
#define MINUS 2
#define MULTIPLICATION 3
#define DIVISION 4

int operator_ = PLUS;

bool calculation(studypkg::tutorial_srv::Request &req,
         studypkg::tutorial_srv::Response &res)
{
  switch(operator_)
  {
    case PLUS:
      res.result = req.a + req.b; break;
    case MINUS:
      res.result = req.a - req.b; break;
    case MULTIPLICATION:
      res.result = req.a * req.b; break;
    case DIVISION:
      if(req.b == 0) { ROS_INFO("Wrong Input"); break; }
      else { res.result = req.a / req.b; break; }
  }
  
  ROS_INFO("request: x=%ld, y=%ld", (long int)req.a, (long int)req.b);
  ROS_INFO("sending back response: [%ld]", (long int)res.result);
  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "rostutorials_server");
  ros::NodeHandle nh;
  nh.setParam("calculation_method", PLUS); // 초기설정 =  PLUS , 파라미터 이름 = "calculation_method"
  ros::ServiceServer service = nh.advertiseService("ros_tutorial_srv", calculation);
  ROS_INFO("Ready to Calculation");
  
  ros::Rate r(10); // 10Hz 주기설정
  
  while (1)
  {
    nh.getParam("calculation_method",operator_);
    ros::spinOnce();
    r.sleep(); // 무한루프 탈출(루틴반복)
  }
  return 0;
}

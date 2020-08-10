#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <studypkg/FibonacciAction.h>

class FibonacciAction
{
protected:

  ros::NodeHandle nh_;

  actionlib::SimpleActionServer<studypkg::FibonacciAction> as_;

  std::string action_name_;

  //Action feedback & result (usage : publish)
  studypkg::FibonacciFeedback feedback_;
  studypkg::FibonacciResult result_;

public:

  FibonacciAction(std::string name) :
    as_(nh_,name,boost::bind(&FibonacciAction::executeCB, this, _1),false),action_name_(name)
  {
    as_.start();
  }
  ~FibonacciAction(void)
  {
  }

  // excute action(fibonacci)
  void executeCB(const studypkg::FibonacciGoalConstPtr &goal)
  {
    ros::Rate r(1);
    bool success = true;

    feedback_.sequence.clear();
    feedback_.sequence.push_back(0);
    feedback_.sequence.push_back(1);

    ROS_INFO("%s:Executing, creating Fibonacci sequence of order %i with initial seeds %i %i", action_name_.c_str(), goal->order, feedback_.sequence[0],feedback_.sequence[1]);

    for(int i=1; i<=goal->order;i++)
    {
      //action cancle
      if(as_.isPreemptRequested() || !ros::ok())
      {
        ROS_INFO("%s : Preempted", action_name_.c_str());
        as_.setPreempted();
        success=false;
        break;
      }

      //action excute
      feedback_.sequence.push_back(feedback_.sequence[i] + feedback_.sequence[i-1]);
      as_.publishFeedback(feedback_); // publish feedback
      ROS_INFO("Feedback value : %d",feedback_.sequence[i-1]);
      r.sleep();
    }
    if(success)
    {
      result_.sequence = feedback_.sequence;
      ROS_INFO("%s: Succeeded",action_name_.c_str());
      as_.setSucceeded(result_);
    }
  }
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "rostutorials_action_server");
  FibonacciAction fibonacci("ros_tutorial_action"); // Action name : ros_tutorial_action
  ros::spin();
  return 0;
}
#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>




int main(int argc, char **argv)
{
  ros::init(argc, argv, "gpioInput");

  ros::NodeHandle n;

  ros::Publisher pub = n.advertise<std_msgs::String>("gpioData", 1000);

  std_msgs::String msg;

  std::stringstream ss;
  for (int i = 1; i < argc; i++){
  ss << argv[i] << " ";
  }
  msg.data = ss.str();

  pub.publish(msg);


  return 0;
}


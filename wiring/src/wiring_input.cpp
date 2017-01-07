#include "ros/ros.h"
#include "std_msgs/String.h"
#include <iostream>
#include <sstream>
#include <string.h>



int main(int argc, char **argv)
{
  ros::init(argc, argv, "gpioInput");

  ros::NodeHandle n;

  ros::Publisher pub = n.advertise<std_msgs::String>("gpioData", 1000);
while (ros::ok())
  {
  std_msgs::String msg;
  std::string input = "";
  std::stringstream ss;
  getline(std::cin, input);
  ss << input;
  msg.data = ss.str();

  pub.publish(msg);
  ros::spinOnce();
}
  return 0;
}


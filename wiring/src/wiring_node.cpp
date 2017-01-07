#include "ros/ros.h"
#include "std_msgs/String.h"
#include "wiringPi.h"


void gpio(const std_msgs::String::ConstPtr& msg)
{
	std_msgs::String s = msg->data.c_str();
	std_msgs::String delimiter = " ";
	std::vector<int> listOfData;
	size_t pos = 0;
	std_msgs::String token;
	while ((pos = s.find(delimiter)) != std_msgs::String::npos) {
		token = s.substr(0, pos);
		listOfData.push_back(std_msgs::stoi(token));
		s.erase(0, pos + delimiter.length());
	}
	listOfData.push_back(std_msgs::stoi(s));
	if (listOfData.at(0))
	{
		pinMode(listOfData.at(1), OUTPUT);
	}
	else
	{
		digitalWrite(listOfData.at(1), listOfData.at(2));
	}	
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "gpio");
	ros::NodeHandle n;
	wiringPiSetupGpio();
	ros::Subscriber sub = n.subscribe("gpioData", 1000, gpio);
	ros::spin();
	return 0;
}

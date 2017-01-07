#include "ros/ros.h"
#include "std_msgs/String.h"
#include <string>
extern "C" {
#include <wiringPi.h>
}

void gpio(const std_msgs::String::ConstPtr& msg)
{
	std::string s = msg->data.c_str();
	ROS_INFO("%s", msg->data.c_str());
	std::string delimiter = " ";
	std::vector<int> listOfData;
	size_t pos = 0;
	std::string token;
	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		listOfData.push_back(std::stoi(token));
		s.erase(0, pos + delimiter.length());
	}
	listOfData.push_back(std::stoi(s));
	if (listOfData.at(0))
	{
		pinMode(listOfData.at(1), OUTPUT);
	}
	else
	{
		if (listOfData.at(2)){
			digitalWrite(listOfData.at(1), HIGH);
		}
		else
		{
			digitalWrite(listOfData.at(1), LOW);
		}
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

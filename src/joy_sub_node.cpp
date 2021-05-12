#include <ros/ros.h>
#include "joy_sub/joy_sub.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "joy_sub");
    ros::NodeHandle nh;
    ros::NodeHandle private_nh("~");
    joy_sub::JoySubscriber joy_sub(nh, private_nh);

    return 0;
}
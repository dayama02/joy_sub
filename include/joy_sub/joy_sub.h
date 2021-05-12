#ifndef JOY_SUB_H
#define JOY_SUB_H

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>
namespace joy_sub
{
    class JoySubscriber
    {
        public:
            JoySubscriber(ros::NodeHandle nh, ros::NodeHandle private_nh);
            ~JoySubscriber(){};
            ros::NodeHandle nh_;
            ros::NodeHandle private_nh_;
            ros::Publisher cmd_vel_pub_;
            ros::Subscriber joy_sub_;
            ros::Subscriber cmd_vel_sub_;
            geometry_msgs::Twist cmd_vel_msg_;

        protected:
            void init();
            void run();
            void joyCallback(const sensor_msgs::JoyConstPtr& msg_raw);
            void cmdVelCallback(const geometry_msgs::TwistConstPtr& msg_raw);
    };
}

#endif
#include "joy_sub/joy_sub.h"

namespace joy_sub
{
    JoySubscriber::JoySubscriber(ros::NodeHandle nh, ros::NodeHandle private_nh) :
    nh_(nh), private_nh_(private_nh)
    {
        init();
        run();
    }

    void JoySubscriber::init()
    {
        joy_sub_ = nh_.subscribe("/joy", 10, &JoySubscriber::joyCallback, this);
        cmd_vel_sub_ = nh_.subscribe("/cmd_vel", 10, &JoySubscriber::cmdVelCallback, this);
        cmd_vel_pub_ = private_nh_.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

        ros::Duration(1.0).sleep();
        ROS_INFO("JoySubscriber: Initialized");
    }


    void JoySubscriber::run()
    {
        ros::Rate rate(10);
        while(ros::ok()){
            ros::spinOnce();
            rate.sleep();
        }
    }

    void JoySubscriber::joyCallback(const sensor_msgs::JoyConstPtr& msg_raw)
    {
        // 処理内容を記述
        ROS_INFO("LEFT X:%1.1f Y:%1.1f, RIGHT X:%1.1f Y:%1.1f", msg_raw->axes[0], 
                                                                msg_raw->axes[1], 
                                                                msg_raw->axes[3], 
                                                                msg_raw->axes[4]);
        cmd_vel_msg_.linear.x = msg_raw->axes[1];
        cmd_vel_msg_.angular.z = msg_raw->axes[3];
        cmd_vel_pub_.publish(cmd_vel_msg_);
    }

    void JoySubscriber::cmdVelCallback(const geometry_msgs::TwistConstPtr& msg_raw)
    {
        ROS_INFO("CMD X:%1.1f Z%1.1f", msg_raw->linear.x, msg_raw->angular.z);
    }
}
#include <ros/ros.h>

#include <nlink_unpack/nlink_linktrack_nodeframe2.h>
#include <iomanip>
#include <iostream>
#include <std_msgs/String.h>
#include <sstream>
#include <sensor_msgs/Imu.h>
#include <nlink_parser/LinktrackNodeframe2.h>

// void doMsg (const nlink_parser::LinktrackNodeframe2& msg ){



//     sensor_msgs::Imu imu_data;

//     imu_data.header.stamp = ros::Time::now();
//     imu_data.header.frame_id = "base_link";
//     imu_data.orientation.x = msg.quaternion[0];
//     imu_data.orientation.y = msg.quaternion[1];
//     imu_data.orientation.z = msg.quaternion[2];
//     imu_data.orientation.w = msg.quaternion[3];


//     imu_data.angular_velocity.x = msg.imu_gyro_3d[0];
//     imu_data.angular_velocity.y = msg.imu_gyro_3d[1];
//     imu_data.angular_velocity.z = msg.imu_gyro_3d[2];

     
//     imu_data.linear_acceleration.x = msg.imu_acc_3d[0];
//     imu_data.linear_acceleration.y = msg.imu_acc_3d[1];
//     imu_data.linear_acceleration.z = msg.imu_acc_3d[2];

//     pub.publish(imu_data);

// }



// int main(int argc, char  *argv[])
// {

//     ros::init(argc,argv,"sub_noodloop");
//     ros::NodeHandle nh;
//     ros::Publisher pub = nh.advertise<sensor_msgs::Imu>("imu_data", 200);
//     // sensor_msgs::Imu imu_data;
//     ros::Subscriber sub = nh.subscribe("nlink_linktrack_nodeframe2", 200 , doMsg);
    
    
    
//     ros::spin(); //repeatly receive
//     /* code */
//     return 0;
// }






using namespace std;


class SubscribeAndPublish
{
public:
  SubscribeAndPublish()
  {
    //Topic you want to publish
    pub_ = n_.advertise<sensor_msgs::Imu>("imu_data", 200);
    //Topic you want to subscribe
    sub_ = n_.subscribe("nlink_linktrack_nodeframe2", 200 , &SubscribeAndPublish::callback, this);
  }

  void callback(const nlink_parser::LinktrackNodeframe2& msg)
  {
    //PUBLISHED_MESSAGE_TYPE output;
    //.... do something with the input and generate the output...
    sensor_msgs::Imu imu_data;

    imu_data.header.stamp = ros::Time::now();
    imu_data.header.frame_id = "base_link";
    imu_data.orientation.x = msg.quaternion[0];
    imu_data.orientation.y = msg.quaternion[1];
    imu_data.orientation.z = msg.quaternion[2];
    imu_data.orientation.w = msg.quaternion[3];
    imu_data.orientation_covariance = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0};

    imu_data.angular_velocity.x = msg.imu_gyro_3d[0];
    imu_data.angular_velocity.y = msg.imu_gyro_3d[1];
    imu_data.angular_velocity.z = msg.imu_gyro_3d[2];
    imu_data.angular_velocity_covariance = {2.76e-09, 0.0, 0.0, 0.0, 2.297382402110541e-09, 0.0, 0.0, 0.0, 2.8645826590988875e-09};
     
    imu_data.linear_acceleration.x = msg.imu_acc_3d[0];
    imu_data.linear_acceleration.y = msg.imu_acc_3d[1];
    imu_data.linear_acceleration.z = msg.imu_acc_3d[2];
    imu_data.linear_acceleration_covariance = {4.608023473906542e-08, 0.0, 0.0, 0.0, 2.1782662784630702e-08, 0.0, 0.0, 0.0, 1.9978775966933426e-08};

    pub_.publish(imu_data);
  }


private:
  ros::NodeHandle n_; 
  ros::Publisher pub_;
  ros::Subscriber sub_;

};//End of class SubscribeAndPublish

int main(int argc, char **argv)
{
  //Initiate ROS
  ros::init(argc, argv, "pub_sub");
  
  //Create an object of class SubscribeAndPublish that will take care of everything
  SubscribeAndPublish SAPObject;
  ros::spin();
  return 0;
}

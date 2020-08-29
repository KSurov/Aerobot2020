#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/PoseStamped.h>

void poseCallback(const geometry_msgs::PoseStampedConstPtr& data){
  static tf::TransformBroadcaster br;
  tf::Transform transform;
  transform.setOrigin(tf::Vector3(data->pose.position.x,
                                  data->pose.position.y,
                                  data->pose.position.z));
  tf::Quaternion q(data->pose.orientation.x,
				   data->pose.orientation.y,
				   data->pose.orientation.z,
				   data->pose.orientation.w);
  transform.setRotation(q);
  br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "map", "base_link"));
}

int main(int argc, char** argv){
  ros::init(argc, argv, "robot_tf_publisher");
  ros::NodeHandle n("~");
  ros::Rate r(100);
  
  ros::Subscriber navPosSub;
  navPosSub = n.subscribe("/mavros/local_position/pose", 10, poseCallback);

  tf::TransformBroadcaster broadcaster,broadcaster2,broadcaster3,broadcaster4;

  while(n.ok()){
    broadcaster.sendTransform(
      tf::StampedTransform(
        tf::Transform(tf::Quaternion(0, 0, 0, 1), tf::Vector3(0.0, 0.0, 0.1)),
        ros::Time::now(),"base_link", "rplidar_link"));
    broadcaster2.sendTransform(
      tf::StampedTransform(
        tf::Transform(tf::Quaternion(0.5, -0.5, 0.5, -0.5), tf::Vector3(0.1, 0.0, 0.0)),
        ros::Time::now(),"base_link", "r200"));
    broadcaster3.sendTransform(
      tf::StampedTransform(
        tf::Transform(tf::Quaternion(0, 1, 0, 1), tf::Vector3(0.05, 0.0, -0.05)),
        ros::Time::now(),"base_link", "px4flow"));
    broadcaster4.sendTransform(
      tf::StampedTransform(
        tf::Transform(tf::Quaternion(0, 0, 0, 1), tf::Vector3(0.0, 0.0, -0.1)),
        ros::Time::now(),"base_link", "robot_camera_link"));
	ros::spinOnce();
    r.sleep();
  }
}


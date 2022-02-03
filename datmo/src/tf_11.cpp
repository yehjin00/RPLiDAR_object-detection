#include <ros/ros.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <iostream>

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "tf_11");
    ros::NodeHandle nh;

    std::string place;
    nh.param("place", place, std::string("lab"));

    tf::TransformBroadcaster br_;
    ros::Duration transform_tolerance_;
    transform_tolerance_.fromSec(0.5);
    double lab[4] = {-1.560919, 0.856247, 0.708229, 0.705983};
    double ele[4] = {30.725906, 0.112852, 0.999833, 0.018264};
    ros::Rate rate(20.0);
    while (nh.ok()) {
        tf::Transform map2markermap;
        if(place == std::string("lab")) {
            map2markermap.setOrigin(tf::Vector3(lab[0], lab[1], 0.0));
            tf::Quaternion q(0.000000, 0.000000, lab[2], lab[3]);
            map2markermap.setRotation(q);
        }
        else {
            map2markermap.setOrigin(tf::Vector3(ele[0], ele[1], 0.0));
            tf::Quaternion q(0.000000, 0.000000, ele[2], ele[3]);
            map2markermap.setRotation(q);
        }
        map2markermap.setOrigin(tf::Vector3(-1.560919, 0.856247, 0.0));
        tf::Quaternion q(0.000000, 0.000000, 0.708229, 0.705983);
        map2markermap.setRotation(q);
        ros::Time transform_expiration = ros::Time::now() + transform_tolerance_;
        br_.sendTransform(tf::StampedTransform(map2markermap, transform_expiration, "map", "datmo_lidar"));
        rate.sleep();
    }
    ros::spin();

    return 0;
}

// add_executable(tf_11 src/tf_11.cpp)
// add_dependencies(tf_11 ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
// target_link_libraries(tf_11 ${catkin_LIBRARIES})
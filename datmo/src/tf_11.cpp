#include <ros/ros.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "tf_11");
    ros::NodeHandle nh;

    tf::TransformBroadcaster br_;
    ros::Duration transform_tolerance_;
    transform_tolerance_.fromSec(0.5);

    // -1.538828 0.633258 0.0 0.000000 0.000000 0.660366 0.750944
    ros::Rate rate(20.0);
    while (nh.ok()) {
        tf::Transform map2markermap;
        map2markermap.setOrigin(tf::Vector3(-1.538828, 0.633258, 0.0));
        tf::Quaternion q(0.000000, 0.000000, 0.660366, 0.750944);
        // q.setRPY(0, 0, X_(5 + 3*i) + M_PI);
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
#include <ublox/Product/HpPosRec.h>

void Ublox::Product::HpPosRec::callbackNavRelPosNed(const ublox_msgs::NavRELPOSNED9 &) {
//    std::cerr << "NavReLPoseNEed" << std::endl;


/*    static ros::Publisher imu_pub = nh->advertise<sensor_msgs::Imu>("navheading", kROSQueueSize);

    imu_.header.stamp = ros::Time::now();
    imu_.header.frame_id = frame_id;

    imu_.linear_acceleration_covariance[0] = -1;
    imu_.angular_velocity_covariance[0] = -1;

    double heading = static_cast<double>(m.relPosHeading) * 1e-5 / 180.0 * M_PI;
    tf::Quaternion orientation;
    orientation.setRPY(0, 0, heading);
    imu_.orientation.x = orientation[0];
    imu_.orientation.y = orientation[1];
    imu_.orientation.z = orientation[2];
    imu_.orientation.w = orientation[3];
    // Only heading is reported with an accuracy in 0.1mm units
    imu_.orientation_covariance[0] = 1000.0;
    imu_.orientation_covariance[4] = 1000.0;
    imu_.orientation_covariance[8] = pow(m.accHeading / 10000.0, 2);

    imu_pub.publish(imu_);*/
}
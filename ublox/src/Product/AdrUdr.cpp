#include <ublox/Product/AdrUdr.h>

void Ublox::Product::AdrUdr::callbackEsfMEAS(const ublox_msgs::EsfMEAS &) {
    /*
     *  if (enabled["esf_meas"]) {
    static ros::Publisher imu_pub =
	nh->advertise<sensor_msgs::Imu>("imu_meas", kROSQueueSize);
    static ros::Publisher time_ref_pub =
	nh->advertise<sensor_msgs::TimeReference>("interrupt_time", kROSQueueSize);

    imu_.header.stamp = ros::Time::now();
    imu_.header.frame_id = frame_id;

    float deg_per_sec = pow(2, -12);
    float m_per_sec_sq = pow(2, -10);
    float deg_c = 1e-2;

    std::vector<unsigned int> imu_data = m.data;
    for (int i=0; i < imu_data.size(); i++){
      unsigned int data_type = imu_data[i] >> 24; //grab the last six bits of data
      double data_sign = (imu_data[i] & (1 << 23)); //grab the sign (+/-) of the rest of the data
      unsigned int data_value = imu_data[i] & 0x7FFFFF; //grab the rest of the data...should be 23 bits

      if (data_sign == 0) {
        data_sign = -1;
      } else {
        data_sign = 1;
      }

      //{}//ROS_INFO("data sign (+/-): %f", data_sign); //either 1 or -1....set by bit 23 in the data bitarray

      imu_.orientation_covariance[0] = -1;
      imu_.linear_acceleration_covariance[0] = -1;
      imu_.angular_velocity_covariance[0] = -1;

      if (data_type == 14) {
        if (data_sign == 1) {
	  imu_.angular_velocity.x = 2048 - data_value * deg_per_sec;
        } else {
          imu_.angular_velocity.x = data_sign * data_value * deg_per_sec;
        }
      } else if (data_type == 16) {
        //{}//ROS_INFO("data_sign: %f", data_sign);
        //{}//ROS_INFO("data_value: %u", data_value * m);
        if (data_sign == 1) {
	  imu_.linear_acceleration.x = 8191 - data_value * m_per_sec_sq;
        } else {
          imu_.linear_acceleration.x = data_sign * data_value * m_per_sec_sq;
        }
      } else if (data_type == 13) {
        if (data_sign == 1) {
	  imu_.angular_velocity.y = 2048 - data_value * deg_per_sec;
        } else {
          imu_.angular_velocity.y = data_sign * data_value * deg_per_sec;
        }
      } else if (data_type == 17) {
        if (data_sign == 1) {
	  imu_.linear_acceleration.y = 8191 - data_value * m_per_sec_sq;
        } else {
          imu_.linear_acceleration.y = data_sign * data_value * m_per_sec_sq;
        }
      } else if (data_type == 5) {
        if (data_sign == 1) {
	  imu_.angular_velocity.z = 2048 - data_value * deg_per_sec;
        } else {
          imu_.angular_velocity.z = data_sign * data_value * deg_per_sec;
        }
      } else if (data_type == 18) {
        if (data_sign == 1) {
	  imu_.linear_acceleration.z = 8191 - data_value * m_per_sec_sq;
        } else {
          imu_.linear_acceleration.z = data_sign * data_value * m_per_sec_sq;
        }
      } else if (data_type == 12) {
        //{}//ROS_INFO("Temperature in celsius: %f", data_value * deg_c);
      } else {
        {}//ROS_INFO("data_type: %u", data_type);
        {}//ROS_INFO("data_value: %u", data_value);
      }

      // create time ref message and put in the data
      //t_ref_.header.seq = m.risingEdgeCount;
      //t_ref_.header.stamp = ros::Time::now();
      //t_ref_.header.frame_id = frame_id;

      //t_ref_.time_ref = ros::Time((m.wnR * 604800 + m.towMsR / 1000), (m.towMsR % 1000) * 1000000 + m.towSubMsR);

      //std::ostringstream src;
      //src << "TIM" << int(m.ch);
      //t_ref_.source = src.str();

      t_ref_.header.stamp = ros::Time::now(); // create a new timestamp
      t_ref_.header.frame_id = frame_id;

      time_ref_pub.publish(t_ref_);
      imu_pub.publish(imu_);
    }
  }

  updater->force_update();
     */
}

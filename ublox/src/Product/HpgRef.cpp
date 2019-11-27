#include <ublox/Product/HpgRef.h>

void Ublox::Product::HpgRef::callbackNavSvIn(const ublox_msgs::NavSVIN &) {
}

////
//// u-blox High Precision GNSS Reference Station
////
//void HpgRefProduct::getRosParams() {
//    if (config_on_startup_flag_) {
//        if(nav_rate * meas_rate != 1000)
//        {}//ROS_WARN("For HPG Ref devices, nav_rate should be exactly 1 Hz.");
//
//        if(!getRosUint("tmode3", tmode3_))
//            throw std::runtime_error("Invalid settings: TMODE3 must be set");
//
//        if(tmode3_ == ublox_msgs::CfgTMODE3::FLAGS_MODE_FIXED) {
//            if(!nh->getParam("arp/position", arp_position_))
//                throw std::runtime_error(std::string("Invalid settings: arp/position ")
//                                         + "must be set if TMODE3 is fixed");
//            if(!getRosInt("arp/position_hp", arp_position_hp_))
//                throw std::runtime_error(std::string("Invalid settings: arp/position_hp ")
//                                         + "must be set if TMODE3 is fixed");
//            if(!nh->getParam("arp/acc", fixed_pos_acc_))
//                throw std::runtime_error(std::string("Invalid settings: arp/acc ")
//                                         + "must be set if TMODE3 is fixed");
//            if(!nh->getParam("arp/lla_flag", lla_flag_)) {
//                {}//ROS_WARN("arp/lla_flag param not set, assuming ARP coordinates are %s",
//                "in ECEF");
//                lla_flag_ = false;
//            }
//        } else if(tmode3_ == ublox_msgs::CfgTMODE3::FLAGS_MODE_SURVEY_IN) {
//            nh->param("sv_in/reset", svin_reset_, true);
//            if(!getRosUint("sv_in/min_dur", sv_in_min_dur_))
//                throw std::runtime_error(std::string("Invalid settings: sv_in/min_dur ")
//                                         + "must be set if TMODE3 is survey-in");
//            if(!nh->getParam("sv_in/acc_lim", sv_in_acc_lim_))
//                throw std::runtime_error(std::string("Invalid settings: sv_in/acc_lim ")
//                                         + "must be set if TMODE3 is survey-in");
//        } else if(tmode3_ != ublox_msgs::CfgTMODE3::FLAGS_MODE_DISABLED) {
//            throw std::runtime_error(std::string("tmode3 param invalid. See CfgTMODE3")
//                                     + " flag constants for possible values.");
//        }
//    }
//}
//
//bool HpgRefProduct::configureUblox() {
//    // Configure TMODE3
//    if(tmode3_ == ublox_msgs::CfgTMODE3::FLAGS_MODE_DISABLED) {
//        if(!gps.disableTmode3())
//            throw std::runtime_error("Failed to disable TMODE3.");
//        mode_ = DISABLED;
//    } else if(tmode3_ == ublox_msgs::CfgTMODE3::FLAGS_MODE_FIXED) {
//        if(!gps.configTmode3Fixed(lla_flag_, arp_position_, arp_position_hp_,
//                                  fixed_pos_acc_))
//            throw std::runtime_error("Failed to set TMODE3 to fixed.");
//        if(!gps.configRtcm(rtcm_ids, rtcm_rates))
//            throw std::runtime_error("Failed to set RTCM rates");
//        mode_ = FIXED;
//    } else if(tmode3_ == ublox_msgs::CfgTMODE3::FLAGS_MODE_SURVEY_IN) {
//        if(!svin_reset_) {
//            ublox_msgs::NavSVIN nav_svin;
//            if(!gps.poll(nav_svin))
//                throw std::runtime_error(std::string("Failed to poll NavSVIN while") +
//                                         " configuring survey-in");
//            // Don't reset survey-in if it's already active
//            if(nav_svin.active) {
//                mode_ = SURVEY_IN;
//                return true;
//            }
//            // Don't reset survey-in if it already has a valid value
//            if(nav_svin.valid) {
//                setTimeMode();
//                return true;
//            }
//            ublox_msgs::NavPVT nav_pvt;
//            if(!gps.poll(nav_pvt))
//                throw std::runtime_error(std::string("Failed to poll NavPVT while") +
//                                         " configuring survey-in");
//            // Don't reset survey in if in time mode with a good fix
//            if (nav_pvt.fixType == nav_pvt.FIX_TYPE_TIME_ONLY
//                && nav_pvt.flags & nav_pvt.FLAGS_GNSS_FIX_OK) {
//                setTimeMode();
//                return true;
//            }
//        }
//        // Reset the Survey In
//        // For Survey in, meas rate must be at least 1 Hz
//        uint16_t meas_rate_temp = meas_rate < 1000 ? meas_rate : 1000; // [ms]
//        // If measurement period isn't a factor of 1000, set to default
//        if(1000 % meas_rate_temp != 0)
//            meas_rate_temp = kDefaultMeasPeriod;
//        // Set nav rate to 1 Hz during survey in
//        if(!gps.configRate(meas_rate_temp, (int) 1000 / meas_rate_temp))
//            throw std::runtime_error(std::string("Failed to set nav rate to 1 Hz") +
//                                     "before setting TMODE3 to survey-in.");
//        // As recommended in the documentation, first disable, then set to survey in
//        if(!gps.disableTmode3())
//            //{}//ROS_ERROR("Failed to disable TMODE3 before setting to survey-in.");
//                else
//        mode_ = DISABLED;
//        // Set to Survey in mode
//        if(!gps.configTmode3SurveyIn(sv_in_min_dur_, sv_in_acc_lim_))
//            throw std::runtime_error("Failed to set TMODE3 to survey-in.");
//        mode_ = SURVEY_IN;
//    }
//    return true;
//}
//
//void HpgRefProduct::subscribe() {
//    // Whether to publish Nav Survey-In messages
//    nh->param("publish/nav/svin", enabled["nav_svin"], enabled["nav"]);
//    // Subscribe to Nav Survey-In
//    gps.subscribe<ublox_msgs::NavSVIN>(boost::bind(
//            &HpgRefProduct::callbackNavSvIn, this, _1), kSubscribeRate);
//}
//
//void HpgRefProduct::callbackNavSvIn(ublox_msgs::NavSVIN m) {
//    if(enabled["nav_svin"]) {
//        static ros::Publisher publisher =
//                nh->advertise<ublox_msgs::NavSVIN>("navsvin", kROSQueueSize);
//        publisher.publish(m);
//    }
//
//    last_nav_svin_ = m;
//
//    if(!m.active && m.valid && mode_ == SURVEY_IN) {
//        setTimeMode();
//    }
//
//    updater->update();
//}
//
//bool HpgRefProduct::setTimeMode() {
//    {}//ROS_INFO("Setting mode (internal state) to Time Mode");
//    mode_ = TIME;
//
//    // Set the Measurement & nav rate to user config
//    // (survey-in sets nav_rate to 1 Hz regardless of user setting)
//    if(!gps.configRate(meas_rate, nav_rate))
//        //{}//ROS_ERROR("Failed to set measurement rate to %d ms %s %d", meas_rate,
//        "navigation rate to ", nav_rate);
//    // Enable the RTCM out messages
//    if(!gps.configRtcm(rtcm_ids, rtcm_rates)) {
//        //{}//ROS_ERROR("Failed to configure RTCM IDs");
//        return false;
//    }
//    return true;
//}

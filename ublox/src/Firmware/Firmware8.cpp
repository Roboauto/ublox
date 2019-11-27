#include <ublox/Firmware/Firmware8.h>


//void UbloxFirmware8::getRosParams() {
//    // UPD SOS configuration
//    nh->param("clear_bbr", clear_bbr_, false);
//    gps.setSaveOnShutdown(nh->param("save_on_shutdown", false));
//
//    // GNSS enable/disable
//    nh->param("gnss/gps", enable_gps_, true);
//    nh->param("gnss/galileo", enable_galileo_, false);
//    nh->param("gnss/beidou", enable_beidou_, false);
//    nh->param("gnss/imes", enable_imes_, false);
//    nh->param("gnss/glonass", enable_glonass_, false);
//    nh->param("gnss/qzss", enable_qzss_, false);
//    nh->param("gnss/sbas", enable_sbas_, false);
//    // QZSS Signal Configuration
//    getRosUint("gnss/qzss_sig_cfg", qzss_sig_cfg_,
//               ublox_msgs::CfgGNSS_Block::SIG_CFG_QZSS_L1CA);
//
//    if (enable_gps_ && !supportsGnss("GPS"))
//    {}//ROS_WARN("gnss/gps is true, but GPS GNSS is not supported by %s",
//    "this device");
//    if (enable_glonass_ && !supportsGnss("GLO"))
//    {}//ROS_WARN("gnss/glonass is true, but GLONASS is not supported by %s",
//    "this device");
//    if (enable_galileo_ && !supportsGnss("GAL"))
//    {}//ROS_WARN("gnss/galileo is true, but Galileo GNSS is not supported %s",
//    "by this device");
//    if (enable_beidou_ && !supportsGnss("BDS"))
//    {}//ROS_WARN("gnss/beidou is true, but Beidou GNSS is not supported %s",
//    "by this device");
//    if (enable_imes_ && !supportsGnss("IMES"))
//    {}//ROS_WARN("gnss/imes is true, but IMES GNSS is not supported by %s",
//    "this device");
//    if (enable_qzss_ && !supportsGnss("QZSS"))
//    {}//ROS_WARN("gnss/qzss is true, but QZSS is not supported by this device");
//    if (enable_sbas_ && !supportsGnss("SBAS"))
//    {}//ROS_WARN("gnss/sbas is true, but SBAS is not supported by this device");
//
//    // Fix Service type, used when publishing fix status messages
//    fix_status_service = sensor_msgs::NavSatStatus::SERVICE_GPS
//                         + (enable_glonass_ ? 1 : 0) * sensor_msgs::NavSatStatus::SERVICE_GLONASS
//                         + (enable_beidou_ ? 1 : 0) * sensor_msgs::NavSatStatus::SERVICE_COMPASS
//                         + (enable_galileo_ ? 1 : 0) * sensor_msgs::NavSatStatus::SERVICE_GALILEO;
//
//    //
//    // NMEA Configuration
//    //
//    nh->param("nmea/set", set_nmea_, false);
//    if (set_nmea_) {
//        bool compat, consider;
//        cfg_nmea_.version = cfg_nmea_.VERSION; // message version
//
//        // Verify that parameters are set
//        if (!getRosUint("nmea/version", cfg_nmea_.nmeaVersion))
//            throw std::runtime_error(std::string("Invalid settings: nmea/set is ") +
//                                     "true, therefore nmea/version must be set");
//        if (!getRosUint("nmea/num_sv", cfg_nmea_.numSV))
//            throw std::runtime_error(std::string("Invalid settings: nmea/set is ") +
//                                     "true, therefore nmea/num_sv must be set");
//        if (!getRosUint("nmea/sv_numbering", cfg_nmea_.svNumbering))
//            throw std::runtime_error(std::string("Invalid settings: nmea/set is ") +
//                                     "true, therefore nmea/sv_numbering must be set");
//        if (!nh->getParam("nmea/compat", compat))
//            throw std::runtime_error(std::string("Invalid settings: nmea/set is ") +
//                                     "true, therefore nmea/compat must be set");
//        if (!nh->getParam("nmea/consider", consider))
//            throw std::runtime_error(std::string("Invalid settings: nmea/set is ") +
//                                     "true, therefore nmea/consider must be set");
//
//        // set flags
//        cfg_nmea_.flags = compat ? cfg_nmea_.FLAGS_COMPAT : 0;
//        cfg_nmea_.flags |= consider ? cfg_nmea_.FLAGS_CONSIDER : 0;
//        bool temp;
//        nh->param("nmea/limit82", temp, false);
//        cfg_nmea_.flags |= temp ? cfg_nmea_.FLAGS_LIMIT82 : 0;
//        nh->param("nmea/high_prec", temp, false);
//        cfg_nmea_.flags |= temp ? cfg_nmea_.FLAGS_HIGH_PREC : 0;
//        // set filter
//        nh->param("nmea/filter/pos", temp, false);
//        cfg_nmea_.filter |= temp ? cfg_nmea_.FILTER_POS : 0;
//        nh->param("nmea/filter/msk_pos", temp, false);
//        cfg_nmea_.filter |= temp ? cfg_nmea_.FILTER_MSK_POS : 0;
//        nh->param("nmea/filter/time", temp, false);
//        cfg_nmea_.filter |= temp ? cfg_nmea_.FILTER_TIME : 0;
//        nh->param("nmea/filter/date", temp, false);
//        cfg_nmea_.filter |= temp ? cfg_nmea_.FILTER_DATE : 0;
//        nh->param("nmea/filter/gps_only", temp, false);
//        cfg_nmea_.filter |= temp ? cfg_nmea_.FILTER_GPS_ONLY : 0;
//        nh->param("nmea/filter/track", temp, false);
//        cfg_nmea_.filter |= temp ? cfg_nmea_.FILTER_TRACK : 0;
//        // set gnssToFilter
//        nh->param("nmea/gnssToFilter/gps", temp, false);
//        cfg_nmea_.gnssToFilter |= temp ? cfg_nmea_.GNSS_TO_FILTER_GPS : 0;
//        nh->param("nmea/gnssToFilter/sbas", temp, false);
//        cfg_nmea_.gnssToFilter |= temp ? cfg_nmea_.GNSS_TO_FILTER_SBAS : 0;
//        nh->param("nmea/gnssToFilter/qzss", temp, false);
//        cfg_nmea_.gnssToFilter |= temp ? cfg_nmea_.GNSS_TO_FILTER_QZSS : 0;
//        nh->param("nmea/gnssToFilter/glonass", temp, false);
//        cfg_nmea_.gnssToFilter |= temp ? cfg_nmea_.GNSS_TO_FILTER_GLONASS : 0;
//        nh->param("nmea/gnssToFilter/beidou", temp, false);
//        cfg_nmea_.gnssToFilter |= temp ? cfg_nmea_.GNSS_TO_FILTER_BEIDOU : 0;
//
//        getRosUint("nmea/main_talker_id", cfg_nmea_.mainTalkerId);
//        getRosUint("nmea/gsv_talker_id", cfg_nmea_.gsvTalkerId);
//
//        std::vector<uint8_t> bdsTalkerId;
//        getRosUint("nmea/bds_talker_id", bdsTalkerId);
//        cfg_nmea_.bdsTalkerId[0] = bdsTalkerId[0];
//        cfg_nmea_.bdsTalkerId[1] = bdsTalkerId[1];
//    }
//}
//
//
//bool UbloxFirmware8::configureUblox() {
//    if(clear_bbr_) {
//        // clear flash memory
//        if(!gps.clearBbr())
//        //{}//ROS_ERROR("u-blox failed to clear flash memory");
//    }
//    //
//    // Configure the GNSS, only if the configuration is different
//    //
//    // First, get the current GNSS configuration
//    ublox_msgs::CfgGNSS cfg_gnss;
//    if (gps.poll(cfg_gnss)) {
//        //{}//ROS_DEBUG("Read GNSS config.");
//        //{}//ROS_DEBUG("Num. tracking channels in hardware: %i", cfg_gnss.numTrkChHw);
//        //{}//ROS_DEBUG("Num. tracking channels to use: %i", cfg_gnss.numTrkChUse);
//    } else {
//        throw std::runtime_error("Failed to read the GNSS config.");
//    }
//
//    // Then, check the configuration for each GNSS. If it is different, change it.
//    bool correct = true;
//    for (int i = 0; i < cfg_gnss.blocks.size(); i++) {
//        ublox_msgs::CfgGNSS_Block block = cfg_gnss.blocks[i];
//        if (block.gnssId == block.GNSS_ID_GPS
//            && enable_gps_ != (block.flags & block.FLAGS_ENABLE)) {
//            correct = false;
//            cfg_gnss.blocks[i].flags =
//                    (cfg_gnss.blocks[i].flags & ~block.FLAGS_ENABLE) | enable_gps_;
//            //{}//ROS_DEBUG("GPS Configuration is different");
//        } else if (block.gnssId == block.GNSS_ID_SBAS
//                   && enable_sbas_ != (block.flags & block.FLAGS_ENABLE)) {
//            correct = false;
//            cfg_gnss.blocks[i].flags =
//                    (cfg_gnss.blocks[i].flags & ~block.FLAGS_ENABLE) | enable_sbas_;
//            //{}//ROS_DEBUG("SBAS Configuration is different");
//        } else if (block.gnssId == block.GNSS_ID_GALILEO
//                   && enable_galileo_ != (block.flags & block.FLAGS_ENABLE)) {
//            correct = false;
//            cfg_gnss.blocks[i].flags =
//                    (cfg_gnss.blocks[i].flags & ~block.FLAGS_ENABLE) | enable_galileo_;
//            //{}//ROS_DEBUG("Galileo GNSS Configuration is different");
//        } else if (block.gnssId == block.GNSS_ID_BEIDOU
//                   && enable_beidou_ != (block.flags & block.FLAGS_ENABLE)) {
//            correct = false;
//            cfg_gnss.blocks[i].flags =
//                    (cfg_gnss.blocks[i].flags & ~block.FLAGS_ENABLE) | enable_beidou_;
//            //{}//ROS_DEBUG("BeiDou Configuration is different");
//        } else if (block.gnssId == block.GNSS_ID_IMES
//                   && enable_imes_ != (block.flags & block.FLAGS_ENABLE)) {
//            correct = false;
//            cfg_gnss.blocks[i].flags =
//                    (cfg_gnss.blocks[i].flags & ~block.FLAGS_ENABLE) | enable_imes_;
//        } else if (block.gnssId == block.GNSS_ID_QZSS
//                   && (enable_qzss_ != (block.flags & block.FLAGS_ENABLE)
//                       || (enable_qzss_
//                           && qzss_sig_cfg_ != (block.flags & block.FLAGS_SIG_CFG_MASK)))) {
//            //{}//ROS_DEBUG("QZSS Configuration is different %u, %u",
//            block.flags & block.FLAGS_ENABLE,
//                    enable_qzss_);
//            correct = false;
//            //{}//ROS_DEBUG("QZSS Configuration: %u", block.flags);
//            cfg_gnss.blocks[i].flags =
//                    (cfg_gnss.blocks[i].flags & ~block.FLAGS_ENABLE) | enable_qzss_;
//            //{}//ROS_DEBUG("QZSS Configuration: %u", cfg_gnss.blocks[i].flags);
//            if (enable_qzss_)
//                // Only change sig cfg if enabling
//                cfg_gnss.blocks[i].flags |= qzss_sig_cfg_;
//        } else if (block.gnssId == block.GNSS_ID_GLONASS
//                   && enable_glonass_ != (block.flags & block.FLAGS_ENABLE)) {
//            correct = false;
//            cfg_gnss.blocks[i].flags =
//                    (cfg_gnss.blocks[i].flags & ~block.FLAGS_ENABLE) | enable_glonass_;
//            //{}//ROS_DEBUG("GLONASS Configuration is different");
//        }
//    }
//
//    // If the GNSS is already configured correctly, do not re-configure GNSS
//    // since this requires a cold reset
//    if (correct)
//        //{}//ROS_DEBUG("U-Blox GNSS configuration is correct. GNSS not re-configured.");
//            else if (!gps.configGnss(cfg_gnss, boost::posix_time::seconds(15)))
//        throw std::runtime_error(std::string("Failed to cold reset device ") +
//                                 "after configuring GNSS");
//
//    //
//    // NMEA config
//    //
//    if (set_nmea_ && !gps.configure(cfg_nmea_))
//        throw std::runtime_error("Failed to configure NMEA");
//
//    return true;
//}
//
//void UbloxFirmware8::subscribe() {
//    // Whether to publish Nav PVT messages
//    nh->param("publish/nav/pvt", enabled["nav_pvt"], enabled["nav"]);
//    // Subscribe to Nav PVT
//    gps.subscribe<ublox_msgs::NavPVT>(
//            boost::bind(&UbloxFirmware7Plus::callbackNavPvt, this, _1), kSubscribeRate);
//
//    // Subscribe to Nav SAT messages
//    nh->param("publish/nav/sat", enabled["nav_sat"], enabled["nav"]);
//    if (enabled["nav_sat"])
//        gps.subscribe<ublox_msgs::NavSAT>(boost::bind(
//                publish<ublox_msgs::NavSAT>, _1, "navsat"), kNavSvInfoSubscribeRate);
//
//    // Subscribe to Mon HW
//    nh->param("publish/mon/hw", enabled["mon_hw"], enabled["mon"]);
//    if (enabled["mon_hw"])
//        gps.subscribe<ublox_msgs::MonHW>(boost::bind(
//                publish<ublox_msgs::MonHW>, _1, "monhw"), kSubscribeRate);
//
//    // Subscribe to RTCM messages
//    nh->param("publish/rxm/rtcm", enabled["rxm_rtcm"], enabled["rxm"]);
//    if (enabled["rxm_rtcm"])
//        gps.subscribe<ublox_msgs::RxmRTCM>(boost::bind(
//                publish<ublox_msgs::RxmRTCM>, _1, "rxmrtcm"), kSubscribeRate);
//}
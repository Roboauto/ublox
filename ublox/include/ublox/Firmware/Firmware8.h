#pragma once

#include "IFirmware7.h"

#include <ublox_msgs/NavPVT.h>

namespace Ublox::Firmware {
    class Firmware8 : public IFirmware7<ublox_msgs::NavPVT> {
    public:
        Firmware8(ublox_gps::Gps &gps, RoboCore::SharedDataProvider<RoboCore::Sensor::GPS::Data>& positionProvider) : IFirmware7<ublox_msgs::NavPVT>(gps, positionProvider) {

        }

        unsigned int getFirmwareVersion() override {
            return 8;
        }
    };
}

///**
// *  @brief Implements functions for firmware version 8.
// */
//class UbloxFirmware8 : public UbloxFirmware7Plus<ublox_msgs::NavPVT> {
//public:
//    UbloxFirmware8();
//
//    /**
//     * @brief Get the ROS parameters specific to firmware version 8.
//     *
//     * @details Get the GNSS, NMEA, and UPD settings.
//     */
//    void getRosParams();
//
//    /**
//     * @brief Configure settings specific to firmware 8 based on ROS parameters.
//     *
//     * @details Configure GNSS, if it is different from current settings.
//     * Configure the NMEA if desired by the user. It also may clear the
//     * flash memory based on the ROS parameters.
//     */
//    bool configureUblox();
//
//    /**
//     * @brief Subscribe to u-blox messages which are not generic to all firmware
//     * versions.
//     *
//     * @details Subscribe to NavPVT, NavSAT, MonHW, and RxmRTCM messages based
//     * on user settings.
//     */
//    void subscribe();
//
//private:
//    // Set from ROS parameters
//    //! Whether or not to enable the Galileo GNSS
//    bool enable_galileo_;
//    //! Whether or not to enable the BeiDuo GNSS
//    bool enable_beidou_;
//    //! Whether or not to enable the IMES GNSS
//    bool enable_imes_;
//    //! Whether or not to configure the NMEA settings
//    bool set_nmea_;
//    //! Desired NMEA configuration.
//    ublox_msgs::CfgNMEA cfg_nmea_;
//    //! Whether to clear the flash memory during configuration
//    bool clear_bbr_;
//};
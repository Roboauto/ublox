#pragma once


#include <RoboCore/Sensor/GPS/GPS.h>

#include <ublox_gps/gps.h>
#include <ublox_gps/mkgmtime.h>

namespace Ublox::Firmware {

    long toUtcSeconds(const ublox_msgs::NavPVT& msg) {
        // Create TM struct for mkgmtime
        struct tm time = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        time.tm_year = msg.year - 1900;
        time.tm_mon = msg.month - 1;
        time.tm_mday = msg.day;
        time.tm_hour = msg.hour;
        time.tm_min = msg.min;
        time.tm_sec = msg.sec;
        // C++ STL doesn't have a mkgmtime (though other libraries do)
        // STL mktime converts date/time to seconds in local time
        // A modified version of code external library is used for mkgmtime
        return mkgmtime(&time);
    }

    RoboCore::Sensor::GPS::Data convertNavMSGv9(const ublox_msgs::NavPVT& message) {
        RoboCore::Sensor::GPS::Data gpsData;

        uint8_t validTime = message.VALID_DATE | message.VALID_TIME | message.VALID_FULLY_RESOLVED;

        if (((message.valid & validTime) == validTime) && (message.flags2 & message.FLAGS2_CONFIRMED_AVAILABLE)) {
            //            // Use NavPVT timestamp since it is valid
            gpsData.time = RoboCore::Time::timeFromNanoseconds(message.nano + toUtcSeconds(message) * 1e9);
        } else {
            gpsData.time = RoboCore::Time::Time();
        }

        gpsData.position.latitude = message.lat * 1e-7;  // to deg
        gpsData.position.longitude = message.lon * 1e-7; // to deg
        gpsData.position.height = message.height * 1e-7; // to deg

        // Set the Fix status
        switch (message.fixType) {
            case ublox_msgs::NavPVT::FIX_TYPE_NO_FIX:
                gpsData.fixType = RoboCore::Sensor::GPS::FixType::NoFix;
                break;
            case ublox_msgs::NavPVT::FIX_TYPE_DEAD_RECKONING_ONLY:
                gpsData.fixType = RoboCore::Sensor::GPS::FixType::DeadReckoningOnly;
                break;
            case ublox_msgs::NavPVT::FIX_TYPE_2D:
                gpsData.fixType = RoboCore::Sensor::GPS::FixType::Fix2D;
                break;
            case ublox_msgs::NavPVT::FIX_TYPE_3D:
                gpsData.fixType = RoboCore::Sensor::GPS::FixType::Fix3D;
                break;
            case ublox_msgs::NavPVT::FIX_TYPE_GNSS_DEAD_RECKONING_COMBINED:
                gpsData.fixType = RoboCore::Sensor::GPS::FixType::GNSSAndDeadReckoningCombined;
                break;
            case ublox_msgs::NavPVT::FIX_TYPE_TIME_ONLY:
                gpsData.fixType = RoboCore::Sensor::GPS::FixType::TimeOnly;
                break;
            default:
                throw std::runtime_error("Ublox GPS wrong fix type!" );
        }

        // Set the position covariance
        const double varH = pow(message.hAcc / 1000.0, 2); // to [m^2]
        const double varV = pow(message.vAcc / 1000.0, 2); // to [m^2]

        gpsData.covariance.d_d = varV;
        gpsData.covariance.e_e = varH;
        gpsData.covariance.n_n = varH;

        gpsData.isRtkUsed = (message.flags & ublox_msgs::NavPVT::FLAGS_DIFF_SOLN);

        return gpsData;
    }
}
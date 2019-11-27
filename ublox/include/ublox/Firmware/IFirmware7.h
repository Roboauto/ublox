#pragma once

#include "IFirmware.h"

#include <RoboCore/Signal.h>
#include <RoboCore/Sensor/GPS/GPS.h>
#include <RoboCore/Logging/Logger.h>

#include <ublox_gps/gps.h>
#include <ublox_gps/mkgmtime.h>

namespace Ublox::Firmware {
    /**
     * @brief Abstract class for Firmware versions >= 7.
     *
     * @details This class keeps track of the last NavPVT message uses it to
     * update the fix diagnostics. It is a template class because the NavPVT message
     * is a different length for firmware versions 7 and 8.
     *
     * @typedef NavPVT the NavPVT message type for the given firmware version
     */
    template<class NavPVT>
    class IFirmware7 : public IFirmware {
    public:
        IFirmware7(ublox_gps::Gps& gps, RoboCore::SharedDataProvider<RoboCore::Sensor::GPS::Data>& positionProvider) : positionProvider_(positionProvider) {
            /* Default rate is 1 Hz in Kumar*/
            gps.subscribe<NavPVT>([this] (const auto& msg) { callbackNavPvt(msg); });
        }
    private:
        long toUtcSeconds(const NavPVT& msg) {
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

        void callbackNavPvt(const NavPVT& message) {
            auto gpsData = std::make_shared<RoboCore::Sensor::GPS::Data>();

            constexpr uint8_t validTime = message.VALID_DATE | message.VALID_TIME | message.VALID_FULLY_RESOLVED;

            if (((message.valid & validTime) == validTime) && (message.flags2 & message.FLAGS2_CONFIRMED_AVAILABLE)) {
//            // Use NavPVT timestamp since it is valid
                gpsData->time = RoboCore::Time::timeFromNanoseconds(message.nano + toUtcSeconds(message) * 1e9) ;
            } else {
                ROBO_ERROR("GPS Time not valid, using system one");
                // Use system time since NavPVT timestamp is not valid
                gpsData->time = getContext().getTime();
            }

            gpsData->position.latitude = message.lat * 1e-7; // to deg
            gpsData->position.longitude = message.lon * 1e-7; // to deg
            gpsData->position.height = message.height * 1e-7; // to deg

            // Set the Fix status
            switch(message.fixType)  {
                case NavPVT::FIX_TYPE_NO_FIX:
                    gpsData->fixType = RoboCore::Sensor::GPS::FixType::NoFix;
                    break;
                case NavPVT::FIX_TYPE_DEAD_RECKONING_ONLY:
                    gpsData->fixType = RoboCore::Sensor::GPS::FixType::DeadReckoningOnly;
                    break;
                case NavPVT::FIX_TYPE_2D:
                    gpsData->fixType = RoboCore::Sensor::GPS::FixType::Fix2D;
                    break;
                case NavPVT::FIX_TYPE_3D:
                    gpsData->fixType = RoboCore::Sensor::GPS::FixType::Fix3D;
                    break;
                case NavPVT::FIX_TYPE_GNSS_DEAD_RECKONING_COMBINED:
                    gpsData->fixType = RoboCore::Sensor::GPS::FixType::GNSSAndDeadReckoningCombined;
                    break;
                case NavPVT::FIX_TYPE_TIME_ONLY:
                    gpsData->fixType = RoboCore::Sensor::GPS::FixType::TimeOnly;
                    break;
                default:
                    ROBO_ERROR("Wrong fix Type");
            }

            // Set the position covariance
            const double varH = pow(message.hAcc / 1000.0, 2); // to [m^2]
            const double varV = pow(message.vAcc / 1000.0, 2); // to [m^2]

            gpsData->covariance.d_d = varV;
            gpsData->covariance.e_e = varH;
            gpsData->covariance.n_n = varH;

            if(message.flags & NavPVT::FLAGS_DIFF_SOLN) {
                std::cerr << "DGPSS" << std::endl;
            } else {
                std::cerr << "WITHOUT DGPS" << std::endl;
            }

            positionProvider_(gpsData);

//        fixPublisher.publish(fix);
//
//        //
//        // Twist message
//        //
//        static ros::Publisher velocityPublisher =
//                nh->advertise<geometry_msgs::TwistWithCovarianceStamped>("fix_velocity",
//                                                                         kROSQueueSize);
//        geometry_msgs::TwistWithCovarianceStamped velocity;
//        velocity.header.stamp = fix.header.stamp;
//        velocity.header.frame_id = frame_id;
//
//        // convert to XYZ linear velocity [m/s] in ENU
//        velocity.twist.twist.linear.x = m.velE * 1e-3;
//        velocity.twist.twist.linear.y = m.velN * 1e-3;
//        velocity.twist.twist.linear.z = -m.velD * 1e-3;
//        // Set the covariance
//        const double covSpeed = pow(m.sAcc * 1e-3, 2);
//        const int cols = 6;
//        velocity.twist.covariance[cols * 0 + 0] = covSpeed;
//        velocity.twist.covariance[cols * 1 + 1] = covSpeed;
//        velocity.twist.covariance[cols * 2 + 2] = covSpeed;
//        velocity.twist.covariance[cols * 3 + 3] = -1;  //  angular rate unsupported
//
//        velocityPublisher.publish(velocity);
//
//        //
//        // Update diagnostics
//        //
//        last_nav_pvt_ = m;
//        freq_diag->diagnostic->tick(fix.header.stamp);
//        updater->update();
//    }

        }
    protected:
        RoboCore::SharedDataProvider<RoboCore::Sensor::GPS::Data>& positionProvider_;
    };
}

//template<typename NavPVT>
//class UbloxFirmware7Plus : public UbloxFirmware {
//public:


//
//protected:
//
//    //! The last received NavPVT message
//    NavPVT last_nav_pvt_;
//    // Whether or not to enable the given GNSS
//    //! Whether or not to enable GPS
//    bool enable_gps_;
//    //! Whether or not to enable GLONASS
//    bool enable_glonass_;
//    //! Whether or not to enable QZSS
//    bool enable_qzss_;
//    //! Whether or not to enable SBAS
//    bool enable_sbas_;
//    //! The QZSS Signal configuration, see CfgGNSS message
//    uint32_t qzss_sig_cfg_;
//};
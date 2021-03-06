#pragma once

#include "IProduct.h"
#include <ublox_gps/gps.h>

namespace Ublox::Product {
   /**
    * @brief Implements functions for High Precision GNSS Reference station
    * devices.
    */
    class HpgRef : public IProduct {
    public:
        HpgRef(ublox_gps::Gps& gps) {
            // rate is 1 hz in Kumar
            gps.subscribe<ublox_msgs::NavSVIN>([this]( const auto& msg) { callbackNavSvIn(msg); }/*,1*/);
        }

    private:
        void callbackNavSvIn(const ublox_msgs::NavSVIN &m);
    };
}

//class HpgRefProduct: public virtual ComponentInterface {
//public:
//    /**
//     * @brief Get the ROS parameters specific to the Reference Station
//     * configuration.
//     *
//     * @details Get the TMODE3 settings, the parameters it gets depends on the
//     * tmode3 parameter. For example, it will get survey-in parameters if the
//     * tmode3 parameter is set to survey in or it will get the fixed parameters if
//     * it is set to fixed.
//     */
//    void getRosParams();
//
//    /**
//     * @brief Configure the u-blox Reference Station settings.
//     *
//     * @details Configure the TMODE3 settings and sets the internal state based
//     * on the TMODE3 status. If the TMODE3 is set to fixed, it will configure
//     * the RTCM messages.
//     * @return true if configured correctly, false otherwise
//     */
//    bool configureUblox();
//
//    /**
//     * @brief Subscribe to u-blox Reference Station messages.
//     *
//     * @details Subscribe to NavSVIN messages based on user parameters.
//     */
//    void subscribe();
//    /**
//     * @brief Update the last received NavSVIN message and call diagnostic updater
//     *
//     * @details When the survey in finishes, it changes the measurement &
//     * navigation rate to the user configured values and enables the user
//     * configured RTCM messages. Publish received Nav SVIN messages if enabled.
//     * @param m the message to process
//     */
//    void callbackNavSvIn(ublox_msgs::NavSVIN m);
//
//protected:
//    /**
//     * @brief Update the TMODE3 diagnostics.
//     *
//     * @details Updates the status of the survey-in if in  survey-in mode or the
//     * RTCM messages if in time mode.
//     */
//    void tmode3Diagnostics(diagnostic_updater::DiagnosticStatusWrapper& stat);
//
//    /**
//     * @brief Set the device mode to time mode (internal state variable).
//     *
//     * @details Configure the RTCM messages and measurement and navigation rate.
//     */
//    bool setTimeMode();
//
//    //! The last received Nav SVIN message
//    ublox_msgs::NavSVIN last_nav_svin_;
//
//    //! TMODE3 to set, such as disabled, survey-in, fixed
//    uint8_t tmode3_;
//
//    // TMODE3 = Fixed mode settings
//    //! True if coordinates are in LLA, false if ECEF
//    /*! Used only for fixed mode */
//    bool lla_flag_;
//    //! Antenna Reference Point Position [m] or [deg]
//    /*! Used only for fixed mode */
//    std::vector<float> arp_position_;
//    //! Antenna Reference Point Position High Precision [0.1 mm] or [deg * 1e-9]
//    /*! Used only for fixed mode */
//    std::vector<int8_t> arp_position_hp_;
//    //! Fixed Position Accuracy [m]
//    /*! Used only for fixed mode */
//    float fixed_pos_acc_;
//
//    // Settings for TMODE3 = Survey-in
//    //! Whether to always reset the survey-in during configuration.
//    /*!
//     * If false, it only resets survey-in if there's no fix and TMODE3 is
//     * disabled before configuration.
//     * This variable is used only if TMODE3 is set to survey-in.
//     */
//    bool svin_reset_;
//    //! Measurement period used during Survey-In [s]
//    /*! This variable is used only if TMODE3 is set to survey-in. */
//    uint32_t sv_in_min_dur_;
//    //! Survey in accuracy limit [m]
//    /*! This variable is used only if TMODE3 is set to survey-in. */
//    float sv_in_acc_lim_;
//
//    //! Status of device time mode
//    enum {
//        INIT, //!< Initialization mode (before configuration)
//        FIXED, //!< Fixed mode (should switch to time mode almost immediately)
//        DISABLED, //!< Time mode disabled
//        SURVEY_IN, //!< Survey-In mode
//        TIME //!< Time mode, after survey-in or after configuring fixed mode
//    } mode_;
//};
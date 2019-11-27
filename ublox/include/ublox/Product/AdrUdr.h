#pragma once

#include "IProduct.h"
#include <ublox_gps/gps.h>

namespace Ublox::Product {
   /**
    * @brief Implements functions for High Precision GNSS Reference station
    * devices.
    */
    class AdrUdr : public IProduct {
    public:
        AdrUdr(ublox_gps::Gps& gps) {
            // rate is 1 hz in Kumar
            gps.subscribe<ublox_msgs::EsfMEAS>([this]( const auto& msg) { callbackEsfMEAS(msg); }/*,1*/);
        }

    private:
        void callbackEsfMEAS(const ublox_msgs::EsfMEAS &m);
    };
}
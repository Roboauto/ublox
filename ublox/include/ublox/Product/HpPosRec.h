#pragma once

#include "HpgRef.h"
#include <ublox_gps/gps.h>

namespace Ublox::Product {
    class HpPosRec : public HpgRef {
    public:
        HpPosRec(ublox_gps::Gps& gps) : HpgRef(gps) {
            // rate is 1 hz in Kumar
            gps.subscribe<ublox_msgs::NavRELPOSNED9>([this]( const auto& msg) { callbackNavRelPosNed(msg);}/*,1*/);
        }

    private:
        void callbackNavRelPosNed(const ublox_msgs::NavRELPOSNED9 &m);
    };
}
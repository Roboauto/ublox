#pragma once

#include "Firmware8.h"

namespace Ublox::Firmware {
    class Firmware9 : public Firmware8 {
    public:
        Firmware9(ublox_gps::Gps &gps, RoboCore::SharedDataProvider<RoboCore::Sensor::GPS::Data>& positionProvider) : Firmware8(gps, positionProvider) {

        }

        unsigned int getFirmwareVersion() override {
            return 9;
        }
    };
}
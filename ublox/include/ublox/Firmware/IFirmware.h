#pragma once

#include <RoboCore/Object.h>

namespace Ublox::Firmware {
class IFirmware : public RoboCore::Object {
    public:
        virtual ~IFirmware() = default;
        virtual unsigned int getFirmwareVersion() = 0;
    private:
    };
}
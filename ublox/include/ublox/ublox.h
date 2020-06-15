#pragma once

#include <ublox_gps/gps.h>

#include <RoboCore/Sensor/GPS/GPS.h>
#include <RoboCore/Worker/Task.h>
#include <RoboCore/Signal.h>

namespace Ublox {

    template<typename SizeType, typename T>
    class Set {
    public:
        Set() = default;

        Set(T  value) {
            set(value,true);
        }

        Set(SizeType v) : mask_{v} {

        }

        auto& operator[](T bit) {
            return mask_[static_cast<SizeType>(bit)];
        }

        void set(T bit, bool val) {
            mask_[static_cast<SizeType>(bit)]= val;
        }

        bool get(T bit) const {
            return mask_[static_cast<SizeType>(bit)];
        }

        unsigned long getMask() const {
            return mask_.to_ulong();
        }

    private:
        std::bitset<static_cast<unsigned int>(T::NumBits)> mask_;
    };

    enum class LoadMask {
        IOPort = 0,
        MsgConf = 1,
        InfMsg = 2,
        NavConf = 3,
        RxmConf = 4,
        SenConf = 8,
        RInvConf = 9,
        AntConf = 10,
        LogConf = 11,
        FrsConf = 12,
        NumBits = 12
    };

    class UbloxGPS : public RoboCore::Sensor::GPS::IGPS , public RoboCore::Worker::Task {
    public:
        UbloxGPS(const std::string &host, unsigned int port) {
            gps_.initializeTcp(host, std::to_string(port));
            processMonVer();
            gps_.setRawDataCallback([this](unsigned char*a, std::size_t&b) {
                onRawData(a,b);
            });
        }

        UbloxGPS(const std::string&dev, std::size_t baudrate, std::size_t uartIn, std::size_t uartOut) {
            gps_.initializeSerial(dev, baudrate, uartIn, uartOut);
            processMonVer();
            gps_.setRawDataCallback([this](unsigned char*a, std::size_t&b) {
                onRawData(a,b);
            });
        }

        ~UbloxGPS(){
            gps_.close();
        }

        void loadFromMemory(const Set<uint32_t, LoadMask>& set);
        void onRTKUpdate(const std::shared_ptr<const std::string>& rtkData);
        RoboCore::SharedDataProvider<std::string> GGANMEAMsgProvider{};

    protected:

        void processMonVer();
        void addProductInterface(std::string productCategory, std::string ref_rov = "");

        void onRawData(unsigned char*data, std::size_t &size);

        ublox_gps::Gps gps_{};
        float protocolVersion_{0};
        std::set<std::string> supported_{};

        //! How long to wait during I/O reset [s]
        constexpr static int resetWait_ = 10;
    };
}
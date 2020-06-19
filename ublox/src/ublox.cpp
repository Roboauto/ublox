#include <ublox/ublox.h>
#include <boost/algorithm/string.hpp>

#include <ublox/navMsgConvert.h>

void Ublox::UbloxGPS::processMonVer() {
    ublox_msgs::MonVER monVer;
    float protocolVersion = 0;
    if (!gps_.poll(monVer)) {
        throw std::runtime_error("Failed to poll MonVER & set relevant settings");
    }

    std::vector<std::string> extensions;
    extensions.reserve(monVer.extension.size());
    for (std::size_t i = 0; i < monVer.extension.size(); ++i) {
        char* end = std::find(monVer.extension[i].field.begin(), monVer.extension[i].field.end(), '\0');
        extensions.push_back(std::string(monVer.extension[i].field.begin(), end));
    }

    for (const auto& extension : extensions) {
        std::size_t found = extension.find("PROTVER");
        if (found != std::string::npos) {
            protocolVersion = ::atof(extension.substr(8, extension.size() - 8).c_str());
            break;
        }
    }

    ROBO_INFO(monVer.swVersion.data() << ", HW VER: " << monVer.hwVersion.data());
    if (protocolVersion < 15) {
        ROBO_FATAL("Protocol version " << protocolVersion << " is not supported");
    }
}

void Ublox::UbloxGPS::loadFromMemory(const Set<uint32_t, LoadMask>& set) {
    ublox_msgs::CfgCFG loadMsg{0, 0, 0, 0};

    loadMsg.loadMask = set.getMask();
    loadMsg.deviceMask = 1;

    if (!gps_.configure(loadMsg)) {
        throw std::runtime_error("Failed to load configuration from memory");
    }

    if (set.get(LoadMask::IOPort)) {
        boost::posix_time::seconds wait(resetWait_);
        gps_.reset(wait);

        if (!gps_.isConfigured()) {
            throw std::runtime_error(std::string("Failed to reset serial I/O") +
                                     "after loading I/O configurations from device memory.");
        }
    }
}

void Ublox::UbloxGPS::onRawData(unsigned char* data, std::size_t& size) {
    if (!GGANMEAMsgProvider.needsPublishing()) {
        return;
    }

    std::string str{reinterpret_cast<char*>(data), size};
    if (str.size() >= 6 && str[0] == '$' && str.substr(3, 3) == "GGA") {
        GGANMEAMsgProvider(std::make_shared<std::string>(str));
    }
}

void Ublox::UbloxGPS::onRTKUpdate(const std::shared_ptr<const std::string>& rtkData) {
    gps_.writeToserial(*rtkData);
}
Ublox::UbloxGPS::UbloxGPS(const std::string& host, unsigned int port, double rateFps) {
    gps_.initializeTcp(host, std::to_string(port));
    processMonVer();

    gps_.subscribe<ublox_msgs::NavPVT>([this](const auto& msg) {
        dataProvider(std::make_shared<RoboCore::Sensor::GPS::Data>(Ublox::Firmware::convertNavMSGv9(msg)));
    },
                                       1);

    gps_.setRawDataCallback([this](unsigned char* a, std::size_t& b) {
        onRawData(a, b);
    });

    gps_.configRate(1000 / rateFps, 1);
}

Ublox::UbloxGPS::UbloxGPS(const std::string& dev, std::size_t baudrate, std::size_t uartIn, std::size_t uartOut, double rateFps) {
    bool err;
    int connectTry = 1;
    do {
        err = 0;
        try {
            gps_.initializeSerial(dev, baudrate, uartIn, uartOut);
        } catch (std::runtime_error& e) {
            err = 1;

            std::cerr << "could not open serial port try:" << connectTry <<" of 10" << std::endl;
            connectTry++;
            if( connectTry > 10){
                throw e;
            }
        }

    } while (err);

    processMonVer();

    gps_.subscribe<ublox_msgs::NavPVT>([this](const auto& msg) {
        dataProvider(std::make_shared<RoboCore::Sensor::GPS::Data>(Ublox::Firmware::convertNavMSGv9(msg)));
    },
                                       1);

    gps_.setRawDataCallback([this](unsigned char* a, std::size_t& b) {
        onRawData(a, b);
    });

    gps_.configRate(1000 / rateFps, 1);
}

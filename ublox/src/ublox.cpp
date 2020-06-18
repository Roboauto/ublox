#include <ublox/ublox.h>
#include <boost/algorithm/string.hpp>

#include <ublox/Firmware/IFirmware7.h>

void Ublox::UbloxGPS::processMonVer(double rateFps) {
    ublox_msgs::MonVER monVer;

    if (!gps_.poll(monVer)) {
        throw std::runtime_error("Failed to poll MonVER & set relevant settings");
    }

    ROBO_INFO(monVer.swVersion.data() << ", HW VER: " << monVer.hwVersion.data());

    std::vector<std::string> extensions;
    extensions.reserve(monVer.extension.size());
    for (std::size_t i = 0; i < monVer.extension.size(); ++i) {
        char* end = std::find(monVer.extension[i].field.begin(), monVer.extension[i].field.end(), '\0');
        extensions.push_back(std::string(monVer.extension[i].field.begin(), end));
    }

    for (const auto& extension : extensions) {
        std::size_t found = extension.find("PROTVER");
        if (found != std::string::npos) {
            protocolVersion_ = ::atof(extension.substr(8, extension.size() - 8).c_str());
            break;
        }
    }

    if (protocolVersion_ < 15) {
        ROBO_FATAL("Protocol version " << protocolVersion_ << " is not supported");
    }

    gps_.subscribe<ublox_msgs::NavPVT>([this](const auto& msg) {
        dataProvider(std::make_shared<RoboCore::Sensor::GPS::Data>(Ublox::Firmware::convertNavMSGv9(msg)));
    },
                                       1);

    gps_.configRate(1000 / rateFps, 1);

    if (protocolVersion_ < 18) {
        throw std::runtime_error("protocolVersion_ < 18 is not supported");
        //        // Final line contains supported GNSS delimited by ;
        //        std::vector<std::string> strs;
        //        if(extensions.size() > 0) {
        //            std::spli::split(strs, extensions[extensions.size() - 1], std::any_of(";"));
        //        }
        //        for(size_t i = 0; i < strs.size(); i++)
        //            supported.insert(strs[i]);
    } else {
        for (std::size_t i = 0; i < extensions.size(); ++i) {
            // Up to 2nd to last line
            if (i < extensions.size() - 2) {
                if (extensions[i].find("FWVER") == 0) {
                    auto interface = extensions[i].substr(6);
                    if (interface.size() > 8) {
                        addProductInterface(interface.substr(0, 3), interface.substr(8, 10));
                    } else {
                        addProductInterface(interface.substr(0, 3));
                    }
                }
            } else if (i >= extensions.size() - 2) {
                std::vector<std::string> strs;
                boost::split(strs, extensions[i], boost::is_any_of(";"));
                std::for_each(strs.begin(), strs.end(), [this](const auto& sup) { supported_.insert(sup); });
            }
        }
    }
}

void Ublox::UbloxGPS::addProductInterface(std::string productCategory, std::string refRov) {
    /*
    if (productCategory.compare("HPG") == 0 && ref_rov.compare("REF") == 0) {
        components_.push_back(ComponentPtr(new HpgRefProduct));
    } else if (product_category.compare("HPG") == 0 && ref_rov.compare("ROV") == 0) {
        components_.push_back(ComponentPtr(new HpgRovProduct));
    } else if (product_category.compare("HPG") == 0) {
        components_.push_back(ComponentPtr(new HpPosRecProduct));
    } else if (product_category.compare("TIM") == 0) {
        components_.push_back(ComponentPtr(new TimProduct));
    } else if (product_category.compare("ADR") == 0 || product_category.compare("UDR") == 0) {
        components_.push_back(ComponentPtr(new AdrUdrProduct));
    } else if (product_category.compare("FTS") == 0) {
        components_.push_back(ComponentPtr(new FtsProduct));
    } else if(product_category.compare("SPG") != 0) {
        ROBO_FATAL("Product category " << product_category << " " << ref_rov << " from MonVER message not recognized." << "options are HPG REF, HPG ROV, HPG #.#, TIM, ADR, UDR, FTS, SPG");
    }*/

    if (productCategory == "HPG" && refRov.empty()) {
        gps_.subscribe<ublox_msgs::NavRELPOSNED9>([](const auto& msg) { (void)msg; });

    } else if (productCategory == "ADR" || productCategory == "UDR") {
        gps_.subscribe<ublox_msgs::EsfMEAS>([](const auto& msg) { (void)msg; });
    } else {
        ROBO_FATAL("Product category " << productCategory << " " << refRov << " is not supported");
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
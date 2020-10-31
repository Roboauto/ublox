#include <ublox/ublox.h>
#include <boost/algorithm/string.hpp>

#include <ublox/Firmware/Firmware9.h>

#include <ublox/Product/HpPosRec.h>
#include <ublox/Product/AdrUdr.h>

void Ublox::UbloxGPS::processMonVer() {
    ublox_msgs::MonVER monVer;

    if (!gps_.poll(monVer)) {
        throw std::runtime_error("Failed to poll MonVER & set relevant settings");
    }

    ROBO_INFO( monVer.swVersion.data() << ", HW VER: " << monVer.hwVersion.data());

    std::vector<std::string> extensions;
    extensions.reserve(monVer.extension.size());
    for(std::size_t i = 0; i < monVer.extension.size(); ++i) {
        auto end = std::find(monVer.extension[i].field.begin(), monVer.extension[i].field.end(), '\0');
        extensions.push_back(std::string(monVer.extension[i].field.begin(), end));
    }

    for(const auto &extension: extensions) {
        std::size_t found = extension.find("PROTVER");
        if (found != std::string::npos) {
            protocolVersion_ = ::atof(extension.substr(8, extension.size() - 8).c_str());
            break;
        }
    }

    addFirmwareInterface(protocolVersion_);

    if(protocolVersion_ < 18) {
        throw std::runtime_error("protocolVersion_ < 18 is not supported");
//        // Final line contains supported GNSS delimited by ;
//        std::vector<std::string> strs;
//        if(extensions.size() > 0) {
//            std::spli::split(strs, extensions[extensions.size() - 1], std::any_of(";"));
//        }
//        for(size_t i = 0; i < strs.size(); i++)
//            supported.insert(strs[i]);
    } else {
        for(std::size_t i = 0; i < extensions.size(); ++i) {
            // Up to 2nd to last line
            if(i < extensions.size() - 2) {
                if(extensions[i].find("FWVER") == 0) {
                    auto interface = extensions[i].substr(6);
                    if(interface.size() > 8) {
                            addProductInterface(interface.substr(0, 3), interface.substr(8, 10));
                    } else {
                            addProductInterface(interface.substr(0, 3));
                    }
                }
            } else if(i >= extensions.size() - 2) {
                std::vector<std::string> strs;
                boost::split(strs, extensions[i], boost::is_any_of(";"));
                std::for_each(strs.begin(), strs.end(), [this] (const auto& sup) {supported_.insert(sup);});
            }
        }
    }
}

void Ublox::UbloxGPS::addFirmwareInterface(float protocolVersion) {

//    if (protocolVersion_ == 0) {
//        ROBO_ERROR("Failed to parse MonVER and determine protocol version. Defaulting to firmware version 6.");
//    }

    /*if (protocolVersion_ < 14) {
        firmwareInterface_ = std::make_shared<Firmware::UbloxFirmware6>();
    } else if (protocolVersion_ >= 14 && protocolVersion_ <= 15) {
        firmwareInterface_ = std::make_shared<Firmware::UbloxFirmware7>();
    */
    //# protocol version for sent commands
    //# u-blox 5, firmware 4 to 6 is protver 10 to 12
    //# u-blox 6, firmware 6 to 7 is protver 12 to 13
    //# u-blox 6, firmware 1 is protver 14
    //# u-blox 7, firmware 1 is protver 14
    //# u-blox 8, is protver 15 to 23
    //# u-blox 9, firmware 1 is protver 27
    if(protocolVersion >= 24) {
        firmwareInterface_ = std::make_shared<Firmware::Firmware9>(gps_, dataProvider);
    } else if(protocolVersion >= 15 ) {
        firmwareInterface_ = std::make_shared<Firmware::Firmware8>(gps_, dataProvider);
    } else {
        ROBO_FATAL("Protocol version " << protocolVersion << " is not supported");
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

    if(productCategory == "HPG" && refRov.empty()) {
        productInterface_ = std::make_shared<Product::HpPosRec>(gps_);
    } else if(productCategory == "ADR" || productCategory == "UDR") {
        productInterface_ = std::make_shared<Product::AdrUdr>(gps_);
    } else {
        ROBO_FATAL("Product category " << productCategory << " " << refRov << " is not supported");
    }
}
void Ublox::UbloxGPS::loadFromMemory(const Set<uint32_t, LoadMask>& set) {
    ublox_msgs::CfgCFG loadMsg{0,0,0,0};

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

void Ublox::UbloxGPS::onRawData(unsigned char*data, std::size_t &size) {
    if(!GGANMEAMsgProvider.needsPublishing()) {
        return;
    }

    std::string str{reinterpret_cast<char*>(data), size};
    if(str.size() >= 6 && str[0] == '$' && str.substr(3,3) == "GGA") {
        GGANMEAMsgProvider(std::make_shared<std::string>(str));
    }
}

void Ublox::UbloxGPS::onRTKUpdate(const std::shared_ptr<const std::string>& rtkData) {
    gps_.writeToserial(*rtkData);
}
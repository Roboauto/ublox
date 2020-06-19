
#include <ublox/ublox.h>

#include <RoboCore/Context/RealTime.h>
#include <RoboCore/Core.h>

#include <RoboCore/RTK/NtripClient.h>


void callback(const  std::shared_ptr<const RoboCore::Sensor::GPS::Data>& data){
   // std::cout << data->position.latitude << std::endl;
   // std::cout << data->position.longitude<< std::endl;
   // std::cout << static_cast<int>(data->fixType) << std::endl;
}

int main(){
    while( 1) {
        std::cout << "start" << std::endl;
        {
            sleep(1);
            RoboCore::Core core;
            auto context = std::make_shared<RoboCore::Context::RealTime>();

            context->getLogger().setDefaultVerbosity(RoboCore::Logging::Verbosity::All);
            core.setContext(context);
            auto contextInjector = RoboCore::withContext(context);
            (void)contextInjector; // TODO: this is necessary to correctly pass context however as it's not used, clang-tidy reports an error

            auto gps = core.addWorker<Ublox::UbloxGPS>("/dev/serial/by-id/usb-u-blox_AG_-_www.u-blox.com_u-blox_GNSS_receiver-if00", 115200, ublox_msgs::CfgPRT::PROTO_UBX, ublox_msgs::CfgPRT::PROTO_UBX);

            auto ntripClient = core.addWorker<RoboCore::RTK::NtripClient>("195.245.209.181", 2111, "roboauto", "robo.Auto1", "/RTK3-MSM");
            RoboCore::connect(gps->GGANMEAMsgProvider, ntripClient, &RoboCore::RTK::NtripClient::onPosition);
            RoboCore::connect(ntripClient->rtkProvider, gps, &Ublox::UbloxGPS::onRTKUpdate);

            gps->dataProvider.addCallback(std::function<void(const std::shared_ptr<const RoboCore::Sensor::GPS::Data>&)>(callback));

            core(RoboCore::Core::ExecutionType::NonBlocking);
            sleep(1);
        }
    }
    return 0;
}
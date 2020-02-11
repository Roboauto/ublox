#include <ublox_gps/callback.h>
#include <ublox_gps/async_worker.h>

namespace ublox_gps {

    void CallbackHandlers::readCallback(unsigned char* data, std::size_t& size) {
        ublox::Reader reader(data, size);
        // Read all U-Blox messages in buffer
        while (reader.search() != reader.end() && reader.found()) {
            if (debug >= 3) {
                // Print the received bytes
                std::ostringstream oss;
                for (ublox::Reader::iterator it = reader.pos(); it != reader.pos() + reader.length() + 8; ++it) {
                    oss << boost::format("%02x") % static_cast<unsigned int>(*it) << " ";
                }
                //ROS_DEBUG("U-blox: reading %d bytes\n%s", reader.length() + 8,
                //         oss.str().c_str());
            }

            handle(reader);
        }

        // delete read bytes from ASIO input buffer
        std::copy(reader.pos(), reader.end(), data);
        size -= reader.pos() - data;
    }
}

#include "echo.h"

namespace backend {
    namespace devices {
        void Echo::AddEndpoint(interfaces::Endpoint *endpoint) {
            this->endpoint = endpoint;
        }

        void Echo::AddEndpoints(std::vector<interfaces::Endpoint*> endpoints) {
            if (!endpoints.empty()) {
                this->endpoint = endpoints[0];
            }
        }

        void Echo::Up() {
            endpoint->Up();
            std::thread temp(&Echo::EchoMessages, this);
            this->isup = true;
        }

        void Echo::Down() {
            endpoint->Down();
            this->isup = false;
        }

        /**
         * @brief This function will echo messages from the endpoint
         * 
         */

        void Echo::EchoMessages() {
            char *buffer;
            int startbuffer = 0;
            char *prevbuffer = new char[4096];
            int prevbuffersize = 0;
            // only will echo messages if the device is up
            while (this->isup) {
                // gets data from the endpoint
                int size = this->endpoint->GetPackets(buffer);
                // checks if there was any leftover data from the previous packet
                if (prevbuffersize > 0) {
                    // adds to the current buffer
                    if (memcpy(prevbuffer + prevbuffersize, buffer, size) != 0) {
                        size = size + prevbuffersize;
                        delete buffer;
                        buffer = prevbuffer;
                    }
                }
                // checks if there is enough data for a 0 size packet
                while (size > 48) {
                    data::Ethernet eth = data::Ethernet(buffer);
                    data::IP ip = data::IP(eth.GetData());
                    // checks if there is enough data for the packet length given
                    if (26 + ip.GetHeaderLength() + ip.GetDataLength() < size - startbuffer) {
                        // copies the leftover bytes to the buffer for the next read
                        if (memcpy(buffer + startbuffer, prevbuffer, size - startbuffer) != 0) {
                            prevbuffersize = size - startbuffer;
                            break;
                        }
                        startbuffer += 26 + ip.GetHeaderLength() + ip.GetDataLength();
                    } else {
                        data::Ethernet neweth = eth;
                        char *source = neweth.source;
                        char *destination = neweth.destination;
                        neweth.source = destination;
                        neweth.destination = source;
                        source = neweth.data.source;
                        destination = neweth.data.destination;
                        neweth.data.source = destination;
                        neweth.data.destination = source;
                        char *out;
                        int size = neweth.GetCharPacket(out);
                        this->endpoint->Receive(out, size);
                    }
                }
            }
        }
    }
}
#include "repeater.h"

namespace backend {
    namespace devices {
        void Repeater::AddEndpoint(interfaces::Endpoint *endpoint) {
            this->endpoint = endpoint;
        }

        void Repeater::Up() {
            endpoint->Up();
            this->isup = true;
        }

        void Repeater::Down() {
            endpoint->Down();
            this->isup = false;
        }

        void Repeater::SendMessages() {
            for (std::map<std::string, std::string> message : this->messages) {
                endpoint->Send((char*)message["data"].c_str(), message["data"].length());
            }
        }
    }
}
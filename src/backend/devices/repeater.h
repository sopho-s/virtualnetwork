#include "device.h"
#include <vector>
#include <map>
#include <string>
#pragma once

namespace backend {
    namespace devices {
        class Repeater : public Device {
            private:
                interfaces::Endpoint* endpoint;
                std::vector<std::map<std::string, std::string>> messages;
                bool isup = false;
                void SendMessages();
            public:
                Repeater() {};
                void AddEndpoint(interfaces::Endpoint *endpoint);
                void Up();
                void Down();
        };
    }
}
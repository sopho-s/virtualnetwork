#include "device.h"
#include "../data/packets.h"
#include <vector>
#include <map>
#include <string>
#include <string.h>
#include <thread>
#include <stdio.h>
#pragma once

namespace backend {
    namespace devices {
        class Echo : public Device {
            private:
                interfaces::Endpoint* endpoint;
                bool isup = false;
                std::thread echothread;
            public:
                Echo() {};
                void AddEndpoint(interfaces::Endpoint *endpoint);
                void AddEndpoints(std::vector<interfaces::Endpoint*> endpoints);
                void Up();
                void Down();
                void EchoMessages();
        };
    }
}
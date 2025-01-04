#include "../interfaces/endpoint.h"
#include <vector>
#pragma once

namespace backend {
    namespace devices {
        class Device {
            private:
                interfaces::Endpoint* endpoint;
                bool isup = false;
            public:
                Device() {};
                void virtual AddEndpoint(interfaces::Endpoint *endpoint) = 0;
                void virtual AddEndpoints(std::vector<interfaces::Endpoint*> endpoints) = 0;
                void virtual Up() = 0;
                void virtual Down() = 0;
        };
    }
}
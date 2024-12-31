#include "../interfaces/endpoint.h"
#include <map>
#include <string>
#include <vector>

#pragma once
namespace backend {
    namespace data {
        class Network {
            private:
                std::map<std::string, interfaces::Endpoint*> endpoints;
                std::vector<std::string> endpointnames;
            public:
                Network();
                void AddEndpoint(std::string name, interfaces::Endpoint* endpoint);
                void ConnectEndpoints(std::string endpoint1, std::string endpoint2);
                void SendData(std::string endpoint, char *data, int amount);
        };
    }
}
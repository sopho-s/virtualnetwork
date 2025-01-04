#include "../interfaces/endpoint.h"
#include "../devices/device.h"
#include <map>
#include <string>
#include <vector>
#include <cstdlib>

#pragma once
namespace backend {
    namespace data {
        class Network {
            private:
                std::map<std::string, interfaces::Endpoint*> endpoints;
                std::map<std::string, devices::Device*> devices;
                std::vector<std::string> endpointnames;
                std::vector<std::string> devicenames;
                std::vector<std::string> connections;
                bool isup = false;
            public:
                Network();
                void AddEndpoint(std::string name, interfaces::Endpoint* endpoint);
                void AddDevice(std::string name, devices::Device* device);
                void ConnectEndpoints(std::string endpoint1, std::string endpoint2);
                void SendData(std::string endpoint, char *data, int amount);
                interfaces::Endpoint* GetEndpoint(std::string name) {
                    return endpoints[name];
                }
                void Up();
                void Down();
        };
    }
}
#include <map>
#include <string>
#include <vector>
#pragma once

namespace backend
{
    namespace data
    {
        class DeviceGraph
        {
            private:
                std::vector<std::map<std::string, std::string>> endpoints;
                std::vector<std::map<std::string, std::string>> devices;
                std::vector<std::map<std::string, std::string>> connections;
            public:
                DeviceGraph();
                void AddDevice(std::map<std::string, std::string> device);
                void AddDevices(std::vector<std::map<std::string, std::string>> device);
                void AddConnection(std::string endpoint1, std::string endpoint2);
                void AddConnections(std::vector<std::map<std::string, std::string>> connections);
                void AddEndpoint(std::map<std::string, std::string> endpoint);
                void AddEndpoints(std::vector<std::map<std::string, std::string>> endpoints);
                std::map<std::string, std::string> GetDevice(std::string name);
                std::vector<std::map<std::string, std::string>> GetAllDevices();
                std::vector<std::map<std::string, std::string>> GetAllEndpoints();
                std::vector<std::map<std::string, std::string>> GetAllConnections();
        };
    }
}
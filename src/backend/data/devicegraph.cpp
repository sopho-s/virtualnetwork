#include "devicegraph.h"

namespace backend {
    namespace data {
        DeviceGraph::DeviceGraph() {
            this->devices = std::vector<std::map<std::string, std::string>>();
            this->connections = std::vector<std::map<std::string, std::string>>();
        }

        void DeviceGraph::AddDevice(std::map<std::string, std::string> device) {
            this->devices.push_back(device);
        }

        void DeviceGraph::AddDevices(std::vector<std::map<std::string, std::string>> devices) {
            for (auto device : devices) {
                this->devices.push_back(device);
            }
        }

        void DeviceGraph::AddConnection(std::string endpoint1, std::string endpoint2) {
            std::map<std::string, std::string> connection;
            connection["endpoint1"] = endpoint1;
            connection["endpoint2"] = endpoint2;
            this->connections.push_back(connection);
        }
        
        void DeviceGraph::AddConnections(std::vector<std::map<std::string, std::string>> connections) {
            for (auto connection : connections) {
                this->connections.push_back(connection);
            }
        }

        void DeviceGraph::AddEndpoint(std::map<std::string, std::string> endpoint) {
            this->endpoints.push_back(endpoint);
        }

        void DeviceGraph::AddEndpoints(std::vector<std::map<std::string, std::string>> endpoints) {
            for (auto endpoint : endpoints) {
                this->endpoints.push_back(endpoint);
            }
        }

        std::map<std::string, std::string> DeviceGraph::GetDevice(std::string name) {
            for (auto device : this->devices) {
                if (device["name"] == name) {
                    return device;
                }
            }
            return std::map<std::string, std::string>();
        }

        std::vector<std::map<std::string, std::string>> DeviceGraph::GetAllDevices() {
            return this->devices;
        }

        std::vector<std::map<std::string, std::string>> DeviceGraph::GetAllEndpoints() {
            return this->endpoints;
        }

        std::vector<std::map<std::string, std::string>> DeviceGraph::GetAllConnections() {
            return this->connections;
        }
    }
}
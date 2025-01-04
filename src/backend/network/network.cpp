#include "network.h"

namespace backend
{
    namespace data
    {
        Network::Network()
        {
            this->endpoints = std::map<std::string, interfaces::Endpoint*>();
            this->endpointnames = std::vector<std::string>();
        }

        void Network::AddEndpoint(std::string name, interfaces::Endpoint *endpoint)
        {
            this->endpoints[name] = endpoint;
            this->endpointnames.push_back(name);
        }

        void Network::AddDevice(std::string name, devices::Device *device)
        {
            this->devices[name] = device;
            this->devicenames.push_back(name);
        }

        void Network::ConnectEndpoints(std::string endpoint1, std::string endpoint2)
        {
            interfaces::Endpoint *ep1 = this->endpoints[endpoint1];
            interfaces::Endpoint *ep2 = this->endpoints[endpoint2];
            std::string bridge = endpoint1 + "-" + endpoint2;
            std::string command = "ip link add " + bridge + " type bridge";
            system(command.c_str());
            connections.push_back(bridge);
            ep1->Connect(ep2, bridge);
            ep2->Connect(ep1, bridge);
        }

        void Network::SendData(std::string endpoint, char *data, int amount)
        {
            interfaces::Endpoint *ep = this->endpoints[endpoint];
            ep->Send(data, amount);
        }

        void Network::Up()
        {
            for (std::string bridge : this->connections) {
                std::string command = "ip link set " + bridge + " up";
                system(command.c_str());
            }
            for (std::string name : this->endpointnames)
            {
                this->endpoints[name]->Up();
            }
            this->isup = true;
        }

        void Network::Down()
        {
            for (std::string bridge : this->connections) {
                std::string command = "ip link delete " + bridge;
                system(command.c_str());
            }
            for (std::string name : this->endpointnames)
            {
                this->endpoints[name]->Down();
            }
            this->isup = false;
        }
    }
}
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

        void Network::ConnectEndpoints(std::string endpoint1, std::string endpoint2)
        {
            interfaces::Endpoint *ep1 = this->endpoints[endpoint1];
            interfaces::Endpoint *ep2 = this->endpoints[endpoint2];
            ep1->Connect(ep2);
            ep2->Connect(ep1);
        }

        void Network::SendData(std::string endpoint, char *data, int amount)
        {
            interfaces::Endpoint *ep = this->endpoints[endpoint];
            ep->Send(data, amount);
        }
    }
}
#include "initializer.h"

namespace backend
{
    namespace initializer
    {
        data::Network Initialize(data::DeviceGraph& graph)
        {
            std::vector<std::map<std::string, std::string>> endpoints = graph.GetAllEndpoints();
            data::Network network = data::Network();
            for (auto endpoint : endpoints)
            {
                std::string type = endpoint["type"];
                if (type == "NIC")
                {
                    interfaces::Endpoint *nic = new interfaces::NIC(endpoint["MAC"]);
                    network.AddEndpoint(endpoint["name"], nic);
                }
            }
            for (auto connection : graph.GetAllConnections())
            {
                network.ConnectEndpoints(connection["endpoint1"], connection["endpoint2"]);
            }
            return network;
        }

        data::DeviceGraph LoadGraph(std::string path) {
            data::DeviceGraph graph = data::DeviceGraph();
            std::ifstream file(path);
            char *filetext = new char[10000];
            file.read(filetext, 10000);
            rapidxml::xml_document<> doc;
            doc.parse<0>(filetext);
            std::vector<std::map<std::string, std::string>> endpoints = ParseEndpoints(doc.first_node("endpoints"));
            std::vector<std::map<std::string, std::string>> connections = ParseConnections(doc.first_node("network"));
            graph.AddEndpoints(endpoints);
            graph.AddConnections(connections);
            return graph;
        }

        std::vector<std::map<std::string, std::string>> ParseEndpoints(rapidxml::xml_node<> *doc)
        {
            std::vector<std::map<std::string, std::string>> endpoints;
            for (rapidxml::xml_node<> *node = doc->first_node(); node; node = node->next_sibling())
            {
                std::map<std::string, std::string> endpoint;
                std::stringstream ss;
                ss << node->name();
                if (ss.str() == "NIC")
                {
                    endpoint["type"] = "NIC";
                    ss.str("");
                    ss << node->first_node("name")->value();
                    endpoint["name"] = ss.str();
                    ss.str("");
                    ss << node->first_node("mac")->value();
                    endpoint["MAC"] = ss.str();
                    ss.str("");
                    ss << node->first_node("device")->value();
                    endpoint["device"] = ss.str();
                    ss.str("");
                    ss << node->first_attribute("id")->value();
                    endpoint["id"] = ss.str();
                }
                endpoints.push_back(endpoint);
            }
            return endpoints;
        }

        std::vector<std::map<std::string, std::string>> ParseConnections(rapidxml::xml_node<> *doc)
        {
            std::vector<std::map<std::string, std::string>> connections;
            for (rapidxml::xml_node<> *node = doc->first_node(); node; node = node->next_sibling())
            {
                std::map<std::string, std::string> connection;
                std::stringstream ss;
                ss << node->first_node("endpoint1")->value();
                connection["endpoint1"] = ss.str();
                ss.str("");
                ss << node->first_node("endpoint2")->value();
                connection["endpoint2"] = ss.str();
                connections.push_back(connection);
            }
            return connections;
        }
    }
}
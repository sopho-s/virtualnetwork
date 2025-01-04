#include "../data/devicegraph.h"
#include "../interfaces/NIC.h"
#include "../interfaces/endpoint.h"
#include "../network/network.h"
#include "../devices/device.h"
#include "../devices/echo.h"
#include "../../imports/rapidxml/rapidxml.hpp"
#include <vector>
#include <map>
#include <string>
#include <fstream> 
#include <sstream>
#pragma once

namespace backend {
    namespace initializer {
        data::Network Initialize(data::DeviceGraph& graph);
        data::DeviceGraph LoadGraph(std::string path);
        std::vector<std::map<std::string, std::string>> ParseEndpoints(rapidxml::xml_node<> *doc);
        std::vector<std::map<std::string, std::string>> ParseDevices(rapidxml::xml_node<> *doc);
        std::vector<std::map<std::string, std::string>> ParseConnections(rapidxml::xml_node<> *doc);
    }
}
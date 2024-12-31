#include "endpoint.h"
#include "../data/buffer.h"
#include <string>
#include <cstring>
#include <stdexcept>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <net/ethernet.h>
#include <netinet/udp.h>
#include <netpacket/packet.h>
#include <unistd.h>
#include <linux/if.h>
#include <sys/ioctl.h>
#pragma once

namespace backend
{
    namespace interfaces
    {
        class NIC : public Endpoint
        {
            private:
                std::string MAC;
                std::string IP;
                int sock;
                data::Buffer databuff;
                Endpoint *connection;
            public:
                NIC(std::string MAC, std::string IP="nan") {
                    this->MAC = MAC;
                    this->IP = IP;
                }
                //virtual ~NIC();
                void BindNIC(const std::string& iface);
                char* Read(int amount);
                void Receive(char *data, int amount);
                void ListenPackets();
                void SendPacket(char *data, int amount);
                void Send(char* data, int amount);
        };
    }
}

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
#include <cstdlib>
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
                bool isup = false;
                std::string iface;
                void CreateNic(const std::string& iface);
            public:
                NIC(std::string MAC, std::string iface, std::string IP="nan") {
                    this->MAC = MAC;
                    this->IP = IP;
                    this->iface = iface;
                    this->BindNIC(iface);
                }
                //virtual ~NIC();
                void BindNIC(const std::string& iface);
                char* Read(int amount);
                int GetPackets(char* out);
                void Receive(char *data, int amount);
                void ListenPackets();
                void SendPacket(char *data, int amount);
                void Send(char* data, int amount);
                void Up();
                void Down();
                void Connect(Endpoint *endpoint, std::string bridge);
        };
    }
}

#include "NIC.h"

namespace backend
{
    namespace interfaces
    {
        void NIC::BindNIC(const std::string& iface)
        {
            this->sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
            if (this->sock == -1)
            {
                throw std::runtime_error("Failed to create socket");
            }

            struct ifreq ifr;
            std::memset(&ifr, 0, sizeof(ifr));
            std::strncpy(ifr.ifr_name, iface.c_str(), IFNAMSIZ - 1);
            if (ioctl(this->sock, SIOCGIFINDEX, &ifr) == -1)
            {
                throw std::runtime_error("Failed to get interface index");
            }

            struct sockaddr_ll sll;
            std::memset(&sll, 0, sizeof(sll));
            sll.sll_family = AF_PACKET;
            sll.sll_protocol = htons(ETH_P_ALL);
            sll.sll_ifindex = ifr.ifr_ifindex;
            if (bind(this->sock, (struct sockaddr *)&sll, sizeof(sll)) == -1)
            {
                throw std::runtime_error("Failed to bind socket");
            }
        }

        char* NIC::Read(int amount)
        {
            return this->databuff.Read(amount);
        }

        void NIC::Receive(char *data, int amount)
        {
            int size = send(this->sock, data, amount, 0);
            if (size < 0) {
                throw std::runtime_error("Packet send failed");
            }
        }

        void NIC::ListenPackets()
        {
            if (this->sock < 0)
            {
                throw std::runtime_error("Socket is not bound");
            }

            char buffer[4096];
            while (true)
            {
                int size = recv(this->sock, buffer, 4096, 0);
                if (size == -1)
                {
                    throw std::runtime_error("Failed to receive packet");
                }
                this->databuff.Write(buffer, size);
            }
        }

        void NIC::SendPacket(char *data, int amount)
        {
            this->connection->Receive(data, amount);
        }

        void NIC::Send(char *data, int amount)
        {
            this->SendPacket(data, amount);
        }
    }
}
#include <string>
#pragma once

namespace backend {
    namespace interfaces {
        class Endpoint {
            private:
                int ID;
                Endpoint *connection;
                bool isup = false;
            public:
                Endpoint() {};
                //virtual ~Endpoint();
                virtual void Receive(char *data, int amount) = 0;
                virtual void Send(char *data, int amount) = 0;
                virtual int GetPackets(char *out) = 0;
                virtual void Up() = 0;
                virtual void Down() = 0;
                //virtual void Send(int amount);
                virtual void Connect(Endpoint *endpoint, std::string bridge) = 0;
        };
    }
}
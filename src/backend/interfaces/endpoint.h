#pragma once

namespace backend {
    namespace interfaces {
        class Endpoint {
            private:
                int ID;
                Endpoint *connection;
            public:
                Endpoint() {};
                //virtual ~Endpoint();
                virtual void Receive(char *data, int amount) = 0;
                virtual void Send(char *data, int amount) = 0;
                //virtual void Send(int amount);
                void Connect(Endpoint *endpoint);
        };
    }
}
#include "endpoint.h"
namespace backend {
    namespace interfaces {
        void Endpoint::Connect(Endpoint *endpoint) {
            this->connection = endpoint;
        }
    }
}
#include <cstdio>
#include "backend/initializer/initializer.h"

int main() {
    backend::data::DeviceGraph devicegraph = backend::initializer::LoadGraph("/home/nick/Documents/virtualnetwork/data/test.xml");
    backend::data::Network network = backend::initializer::Initialize(devicegraph);
    network.Up();
    network.Down();
    return 0;
}
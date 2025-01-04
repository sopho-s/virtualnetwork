#include <string>

namespace backend {
    namespace data {
        class IP {
            public:
                char *version;
                char *headerlength;
                char *service;
                char *length;
                char *identification;
                char *flags;
                char *fragmentoffset;
                char *ttl;
                char *protocol;
                char *checksum;
                char *source;
                char *destination;
                char *data;
                IP() {

                }
                IP(char *data) {
                    this->version = data;
                    this->headerlength = data + 1;
                    this->service = data + 2;
                    this->length = data + 4;
                    this->identification = data + 6;
                    this->flags = data + 8;
                    this->fragmentoffset = data + 10;
                    this->ttl = data + 12;
                    this->protocol = data + 13;
                    this->checksum = data + 14;
                    this->source = data + 16;
                    this->destination = data + 20;
                    this->data = data + 24;
                }
                IP(const IP& other) {
                    this->version = new char[1];
                    this->version[0] = other.version[0];
                    this->headerlength = new char[1];
                    this->headerlength[0] = other.headerlength[0];
                    this->service = new char[2];
                    for (int i = 0; i < 2; i++) {
                        this->service[i] = other.service[i];
                    }
                    this->length = new char[2];
                    for (int i = 0; i < 2; i++) {
                        this->length[i] = other.length[i];
                    }
                    this->identification = new char[2];
                    for (int i = 0; i < 2; i++) {
                        this->identification[i] = other.identification[i];
                    }
                    this->flags = new char[2];
                    for (int i = 0; i < 2; i++) {
                        this->flags[i] = other.flags[i];
                    }
                    this->fragmentoffset = new char[2];
                    for (int i = 0; i < 2; i++) {
                        this->fragmentoffset[i] = other.fragmentoffset[i];
                    }
                    this->ttl = new char[1];
                    this->ttl[0] = other.ttl[0];
                    this->protocol = new char[1];
                    this->protocol[0] = other.protocol[0];
                    this->checksum = new char[2];
                    for (int i = 0; i < 2; i++) {
                        this->checksum[i] = other.checksum[i];
                    }
                    this->source = new char[4];
                    for (int i = 0; i < 4; i++) {
                        this->source[i] = other.source[i];
                    }
                    this->destination = new char[4];
                    for (int i = 0; i < 4; i++) {
                        this->destination[i] = other.destination[i];
                    }
                    this->data = new char[(int)this->length[0] << 8 | (int)this->length[1]];
                    for (int i = 0; i < (int)this->length[0] << 8 | (int)this->length[1]; i++) {
                        this->data[i] = other.data[i];
                    }
                }
                char* GetSource() {
                    return this->source;
                }
                char* GetDestination() {
                    return this->destination;
                }
                char* GetData() {
                    return this->data;
                }
                int GetDataLength() {
                    return (int)this->length[0] << 8 | (int)this->length[1];
                }
                int GetHeaderLength() {
                    return (int)this->headerlength[0] & 0x0F;
                }
                int GetCharPacket(char* out) {
                    out = new char[(int)this->headerlength[0] & 0x0F + (int)this->length[0] << 8 | (int)this->length[1]];
                    out[0] = *this->version;
                    out[1] = *this->headerlength;
                    for (int i = 0; i < 2; i++) {
                        out[i + 2] = this->service[i];
                    }
                    for (int i = 0; i < 2; i++) {
                        out[i + 4] = this->length[i];
                    }
                    for (int i = 0; i < 2; i++) {
                        out[i + 6] = this->identification[i];
                    }
                    for (int i = 0; i < 2; i++) {
                        out[i + 8] = this->flags[i];
                    }
                    for (int i = 0; i < 2; i++) {
                        out[i + 10] = this->fragmentoffset[i];
                    }
                    out[12] = *this->ttl;
                    out[13] = *this->protocol;
                    for (int i = 0; i < 2; i++) {
                        out[i + 14] = this->checksum[i];
                    }
                    for (int i = 0; i < 4; i++) {
                        out[i + 16] = this->source[i];
                    }
                    for (int i = 0; i < 4; i++) {
                        out[i + 20] = this->destination[i];
                    }
                    for (int i = 0; i < (int)this->length[0] << 8 | (int)this->length[1]; i++) {
                        out[i + 24] = this->data[i];
                    }
                    return 24 + (int)this->length[0] << 8 | (int)this->length[1];
                }
        };

        class Ethernet {
            public:
                char *preamble;
                char *source;
                char *destination;
                char *type;
                IP data;
                char *FCS;
                Ethernet(char *data) {
                    this->preamble = data;
                    this->source = data + 8;
                    this->destination = data + 14;
                    this->type = data + 20;
                    this->data = IP(data + 22);
                    this->FCS = data + 22 + this->data.GetHeaderLength() + this->data.GetDataLength();
                }
                Ethernet(const Ethernet& other) {
                    this->preamble = new char[8];
                    for (int i = 0; i < 8; i++) {
                        this->preamble[i] = other.preamble[i];
                    }
                    this->source = new char[6];
                    for (int i = 0; i < 6; i++) {
                        this->source[i] = other.source[i];
                    }
                    this->destination = new char[6];
                    for (int i = 0; i < 6; i++) {
                        this->destination[i] = other.destination[i];
                    }
                    this->type = new char[2];
                    for (int i = 0; i < 2; i++) {
                        this->type[i] = other.type[i];
                    }
                    this->data = other.data;
                    this->FCS = new char[4];
                    for (int i = 0; i < 4; i++) {
                        this->FCS[i] = other.FCS[i];
                    }
                }
                char* GetSource() {
                    return this->source;
                }
                char* GetDestination() {
                    return this->destination;
                }
                char* GetType() {
                    return this->type;
                }
                IP &GetData() {
                    return this->data;
                }
                int GetCharPacket(char* out) {
                    out = new char[26 + this->data.GetHeaderLength() + this->data.GetDataLength()];
                    for (int i = 0; i < 6; i++) {
                        out[i] = this->destination[i];
                    }
                    for (int i = 0; i < 6; i++) {
                        out[i + 6] = this->source[i];
                    }
                    for (int i = 0; i < 2; i++) {
                        out[i + 12] = this->type[i];
                    }
                    char* data;
                    int size = this->data.GetCharPacket(data);
                    for (int i = 0; i < size; i++) {
                        out[i + 14] = data[i];
                    }
                    for (int i = 0; i < 4; i++) {
                        out[i + 14 + size] = this->FCS[i];
                    }
                    return 18 + size;
                }
        };
    }
}
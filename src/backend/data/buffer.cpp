#include "buffer.h"

namespace backend
{
    namespace data
    {
        Buffer::Buffer()
        {
            this->capacity = 65536;
            this->data = new char[this->capacity];
            this->start = 0;
            this->end = 0;
        }

        void Buffer::Write(char *data, int amount)
        {
            for (int i = 0; i < amount; i++)
            {
                this->data[this->end] = data[i];
                this->end = (this->end + 1) % this->capacity;
            }
        }

        char* Buffer::Read(int amount)
        {
            char *result = new char[amount];
            for (int i = 0; i < amount; i++)
            {
                result[i] = this->data[this->start];
                this->start = (this->start + 1) % this->capacity;
                if (this->start == this->end)
                {
                    break;
                }
            }
            return result;
        }
    }
}
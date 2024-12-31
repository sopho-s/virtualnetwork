#pragma once
namespace backend
{
    namespace data
    {
        class Buffer
        {
            private:
                char *data;
                int capacity;
                int start;
                int end;
            public:
                Buffer();
                void Write(char *data, int amount);
                char* Read(int amount);
        };
    }
}
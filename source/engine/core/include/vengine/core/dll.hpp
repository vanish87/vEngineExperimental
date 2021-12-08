
#include <CORE_API.h>

class CORE_API DLLClass
{
    public:
        int i;

    public:
        int DLLFunc(int i);
};

class DLLClassFunc
{
    public:
        int i;

    public:
        CORE_API int DLLFunc(int i);
        CORE_API int DLLFunc1(int i){return 0;};
};

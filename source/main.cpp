
#include <iostream>
#include "vector.h"

using namespace vEngine::Core;

int main(int argc, char* argv[])
{
    std::cout << "Hello World" ;
    Vector<int,2> vec2;
    Vector<int,2> vec21;

    vec2 = vec21;

    Vector<int,3> v3 = 5;

    return 0;
}

#include <iostream>
#include <vector>

#include "vector.h"

using namespace vEngine::Core;

Vector<int, 2> NewVec() { return Vector<int, 2>(); }

int main(int argc, char* argv[])
{
    // std::cout << "Hello World" ;
    // Vector<int,2> vec2;
    // Vector<int,2> vec21;

    // vec2 = vec21;

    std::vector<Vector<int, 2>> moveList{};

    moveList.push_back(Vector<int, 2>());
    moveList.push_back(Vector<int, 2>());

    int a = 1;
    int* b = &a;

    return 0;
}

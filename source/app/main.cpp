#include <iostream>
#include <vector>

#include <lua.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include <vengine/core/vector.hpp>

using namespace vEngine::Core;

Vector<int, 2> NewVec() { return Vector<int, 2>(); }

int main(int argc, char* argv[])
{
    std::cout << "Hello World" << std::endl;
    // Vector<int,2> vec2;
    // Vector<int,2> vec21;

    // vec2 = vec21;

    // Vector<int,2> vec = 1;

    std::vector<Vector<int, 2>> moveList{};

    moveList.push_back(Vector<int, 2>());
    moveList.push_back(Vector<int, 2>());

    int a = 1;
    int* b = &a;

    auto z = Vector<int,2>::Zero();
    auto o = Vector<int,2>::One();

    auto c = z + o;
    auto c1 = c - o;
    c1 += c;

    a++;

    printf("Test");

    auto L = luaL_newstate();
    lua_close(L);

    FT_Library library;
    FT_Face face;

    FT_Error error = FT_Init_FreeType(&library);
    error = FT_Done_FreeType(library);

    return 0;
}

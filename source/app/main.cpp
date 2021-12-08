#include <iostream>
#include <vector>

#include <lua.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include <version.hpp>
#include <engine.hpp>

using namespace vEngine::Core;

Vector<int, 2> NewVec() { return Vector<int, 2>(); }

int main(int argc, char* argv[])
{
    //TODO not working
    #ifdef UNIX
    std::cout << "Hello World from Linux" << std::endl;
    #else
    std::cout << "Hello World from Windows" << std::endl;
    #endif

    std::cout << "Version" + std::string(Version)<<std::endl;
    // Vector<int,2> vec2;
    // Vector<int,2> vec21;

    // vec2 = vec21;

    // Vector<int,2> vec = 1;

    DLLClass dllClass;
    DLLClassFunc dllClassFunc;

    dllClass.DLLFunc(2);
    dllClassFunc.DLLFunc(3);
    dllClassFunc.DLLFunc1(3);

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


    auto L = luaL_newstate();
    lua_close(L);

    FT_Library library;
    FT_Face face;

    FT_Error error = FT_Init_FreeType(&library);
    error = FT_Done_FreeType(library);

    printf("Test\n");
    return 0;
}
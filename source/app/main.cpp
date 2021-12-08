#include <ft2build.h>
#include <windows.h>

#include <iostream>
#include <lua.hpp>
#include <vector>
#include FT_FREETYPE_H

#include <engine.hpp>
#include <version.hpp>

using namespace vEngine::Core;

Vector<int, 2> NewVec()
{
    return Vector<int, 2>();
}

typedef int(__stdcall* f_funci)();

int main(int argc, char* argv[])
{
// TODO not working
#ifdef UNIX
    std::cout << "Hello World from Linux" << std::endl;
#else
    std::cout << "Hello World from Windows" << std::endl;
#endif

    std::cout << "Version" + std::string(Version) << std::endl;
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

    HINSTANCE hGetProcIDDLL = LoadLibrary("d3d11_render_engine.dll");

    if (!hGetProcIDDLL)
    {
        std::cout << "could not load the dynamic library" << std::endl;
        return EXIT_FAILURE;
    }

    // resolve function address here
    f_funci funci = (f_funci)GetProcAddress(hGetProcIDDLL, "Create");
    if (!funci)
    {
        std::cout << "could not locate the function" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "funci() returned " << funci() << std::endl;

    int a = 1;
    int* b = &a;

    auto z = Vector<int, 2>::Zero();
    auto o = Vector<int, 2>::One();

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

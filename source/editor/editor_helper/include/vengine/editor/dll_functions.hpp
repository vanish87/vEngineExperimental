#ifndef _VENGINE_EDITOR_DLL_FUNCTIONS_HPP
#define _VENGINE_EDITOR_DLL_FUNCTIONS_HPP

#pragma once

#include <EDITOR_HELPER_API.h>
#include <engine.hpp>

extern "C" 
{
    EDITOR_HELPER_API void Context_Init(void* hwnd);
    EDITOR_HELPER_API void Context_Deinit();
}

#endif /* _VENGINE_EDITOR_DLL_FUNCTIONS_HPP */

#ifndef _INCLUDE_ENGINE_HPP
#define _INCLUDE_ENGINE_HPP

#pragma once

#ifdef VENGINE_PLATFORM_WINDOWS
    //windows.h should be included first in win32 platform
    #define NOMINMAX
    #include <windows.h>
#endif

#include <VENGINE_API.hpp>

//generated include files
#include <compiler_setting.hpp>
#include <macros.hpp>
#include <defines.hpp>
// #include <version.hpp>

#include <debug.hpp>
#include <interface.hpp>
#include <predeclare.hpp>


// #include <vengine/rendering/data_format.hpp>
// #include <vengine/rendering/data_struct.hpp>
// #include <vengine/rendering/shared/data_cbuffer.hpp>

// Note math.h will include math.hpp
// #include <vengine/core/math.h>

// #include <vengine/core/example_dll.hpp>
// #include <vengine/core/vector.hpp>
// #include <vengine/rendering/render_engine.hpp>

#endif /* _INCLUDE_ENGINE_HPP */

#ifndef _VENGINE_RENDERING_RENDER_ENGINE_HPP
#define _VENGINE_RENDERING_RENDER_ENGINE_HPP

#pragma once

#include <RENDERING_API.h>

#include <engine.hpp>

class RENDERING_API RenderEngine
{
    public:
        virtual void Render() = 0;

    private:
        void CreateInternal();
};

#endif /* _VENGINE_RENDERING_RENDER_ENGINE_HPP */

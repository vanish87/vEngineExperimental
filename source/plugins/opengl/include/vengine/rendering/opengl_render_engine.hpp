#ifndef _PLUGINS_OPENGL_OPENGL_RENDER_ENGINE_HPP
#define _PLUGINS_OPENGL_OPENGL_RENDER_ENGINE_HPP

#include <glad/gl.h>

#include <vengine/rendering/render_engine.hpp>

class RENDERING_API OpenGLRenderEngine : public RenderEngine
{
    public:
        void TestFunc();
        void Render() override;
};

#endif /* _PLUGINS_OPENGL_OPENGL_RENDER_ENGINE_HPP */

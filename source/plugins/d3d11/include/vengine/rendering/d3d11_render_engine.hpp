#ifndef _VENGINE_RENDERING_D3D11_RENDER_ENGINE_HPP
#define _VENGINE_RENDERING_D3D11_RENDER_ENGINE_HPP
#pragma once

#include <vengine/rendering/render_engine.hpp>
namespace vEngine
{
    namespace Rendering
    {
        class D3D11RenderEngine : public RenderEngine
        {
            public:
                void TestFunc();
                void Render() override;
        };

        extern "C" {
            RENDERING_API RenderEngine* Create(void);
        }
    }  // namespace Rendering
}  // namespace vEngine


#endif /* _VENGINE_RENDERING_D3D11_RENDER_ENGINE_HPP */

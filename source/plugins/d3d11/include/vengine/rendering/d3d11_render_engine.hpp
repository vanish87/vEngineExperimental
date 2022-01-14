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
                void CreateRenderWindow() override;
        };

    }  // namespace Rendering
}  // namespace vEngine

extern "C" {
    VENGINE_API void CreateRenderEngine(std::unique_ptr<vEngine::Rendering::RenderEngine>& ptr);
}
#endif /* _VENGINE_RENDERING_D3D11_RENDER_ENGINE_HPP */

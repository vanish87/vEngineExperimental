#ifndef _VENGINE_RENDERING_D3D11_RENDER_OBJECT_FACTORY_HPP
#define _VENGINE_RENDERING_D3D11_RENDER_OBJECT_FACTORY_HPP

#pragma once

#include <vengine/rendering/d3d11_predeclear.hpp>
#include <vengine/core/game_object_factory.hpp>
#include <vengine/rendering/data_struct.hpp>

namespace vEngine
{
    namespace Rendering
    {
        class D3D11RenderObjectFactory : public Core::GameObjectFactory
        {
            public:
                D3D11RenderObjectFactory();
                ~D3D11RenderObjectFactory();
                Core::GameObjectSharedPtr Create(std::any parameter) override;
        };
    }  // namespace Rendering
}  // namespace vEngine


#endif /* _VENGINE_RENDERING_D3D11_RENDER_OBJECT_FACTORY_HPP */

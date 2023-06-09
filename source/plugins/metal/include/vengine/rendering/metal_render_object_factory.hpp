#ifndef _VENGINE_RENDERING_METAL_RENDER_OBJECT_FACTORY_HPP
#define _VENGINE_RENDERING_METAL_RENDER_OBJECT_FACTORY_HPP

#pragma once

// #include <vengine/rendering/metal_predeclear.hpp>
#include <vengine/core/game_object_factory.hpp>
#include <vengine/rendering/data_struct.hpp>

namespace vEngine
{
    namespace Rendering
    {
        class MetalRenderObjectFactory : public Core::GameObjectFactory
        {
            public:
                MetalRenderObjectFactory();
                ~MetalRenderObjectFactory();
                Core::GameObjectSharedPtr Create(std::any parameter) override;
        };
    }  // namespace Rendering
}  // namespace vEngine


#endif /* _VENGINE_RENDERING_METAL_RENDER_OBJECT_FACTORY_HPP */

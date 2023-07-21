#ifndef _VENGINE_CUSTOM_CUSTOM_OBJECT_FACTORY_HPP
#define _VENGINE_CUSTOM_CUSTOM_OBJECT_FACTORY_HPP

#include <engine.hpp>
#include <CUSTOM_PLUGIN_API.hpp>
#include <vengine/core/game_object_factory.hpp>

namespace vEngine
{
    namespace Custom
    {
        class CUSTOM_PLUGIN_API CustomObjectFactory : public Core::GameObjectFactory
        {
            public:
                CustomObjectFactory();
                ~CustomObjectFactory();
                Core::GameObjectSharedPtr Create(std::any parameter) override;
        };
    }  // namespace Custom
}  // namespace vEngine
#endif /* _VENGINE_CUSTOM_CUSTOM_OBJECT_FACTORY_HPP */

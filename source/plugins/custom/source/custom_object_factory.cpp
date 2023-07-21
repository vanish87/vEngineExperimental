
#include <vengine/custom/custom_object_factory.hpp>
#include <vengine/custom/custom_object_example.hpp>

namespace vEngine
{
    namespace Custom
    {
        using namespace vEngine::Core;
        CustomObjectFactory::CustomObjectFactory(){};
        CustomObjectFactory::~CustomObjectFactory(){};
        GameObjectSharedPtr CustomObjectFactory::Create(std::any parameter)
        {
            UNUSED_PARAMETER(parameter);
            PRINT("Custom Create");
            return std::make_shared<CustomObject>();
        }

    }  // namespace Custom

}  // namespace vEngine
extern "C"
{
    CUSTOM_PLUGIN_API void CreateCustomGameObjectFactory(std::unique_ptr<vEngine::Core::GameObjectFactory>& ptr)
    {
        ptr = std::make_unique<vEngine::Custom::CustomObjectFactory>();
    }
    CUSTOM_PLUGIN_API void DestroyCustomGameObjectFactory(std::unique_ptr<vEngine::Core::GameObjectFactory>& ptr)
    {
        ptr.reset();
    }
}

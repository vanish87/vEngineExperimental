
#include <vengine/custom/custom_object_factory.hpp>

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
            return nullptr;
        }

    }  // namespace Custom

}  // namespace vEngine

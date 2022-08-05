/// \file asset_component.cpp
/// \brief source file for Asset Component
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/core/asset_component.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Core
    {

        /// constructor detailed defintion,
        /// should be 2 lines
        AssetComponent::AssetComponent() : Component(GameObjectType::Asset) {}
        AssetComponent::~AssetComponent() {}

        /// A detailed function description, it
        /// should be 2 lines at least.
        int AssetComponent::GetVariable(int p1, float p2)
        {
            UNUSED_PARAMETER(p1);
            UNUSED_PARAMETER(p2);
            return 1;
        }

    }  // namespace Core
}  // namespace vEngine
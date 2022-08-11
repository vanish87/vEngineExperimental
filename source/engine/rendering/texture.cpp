/// \file texture.cpp
/// \brief source file for Texture
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/rendering/texture.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Rendering
    {
        using namespace Core;

        /// constructor detailed defintion,
        /// should be 2 lines
        Texture::Texture(const TextureDescriptor& desc)
        {
            this->descriptor_ = desc;
        }
        Texture::~Texture() {}

        void Texture::PrepareData() {}

        ResourceState Texture::CurrentState()
        {
            return this->current_state_;
        }
        bool Texture::Load(const ResourceDescriptorSharedPtr descriptor)
        {
            UNUSED_PARAMETER(descriptor);
            // auto path = descriptor->file_path;

            // std::ifstream fin(path.string());
            return false;
        }

        /// A detailed function description, it
        /// should be 2 lines at least.
        // int MyClass::GetVariable(int p1, float p2)
        // {
        //     UNUSED_PARAMETER(p1);
        //     UNUSED_PARAMETER(p2);
        //     return 1;
        // }
    }  // namespace Rendering
}  // namespace vEngine
/// \file mesh.hpp
/// \brief Head file for mesh
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_MESH_HPP
#define _VENGINE_CORE_MESH_HPP

#include <vector>

#include <VENGINE_API.h>
#include <engine.hpp>
#include <vengine/core/game_object.hpp>
#include <vengine/core/iresource.hpp>


/// A brief namespace description.
namespace vEngine
{
    namespace Core
    {
        using namespace vEngine::Rendering;
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.

        class Vertex
        {

        };
        class VENGINE_API Mesh : public GameObject, public IResource
        {
            public:
                /// \brief brief constructor description.
                Mesh();
                void Load(const std::string file_name);
                virtual bool Load() override;
                void UpdateGPUBuffer();


                GraphicsBufferSharedPtr vertex_buffer_;
                GraphicsBufferSharedPtr index_buffer_;

                std::vector<Vertex> vertex_data_;

                std::string file_name_;
                //vertex
                //index

        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_MESH_HPP */

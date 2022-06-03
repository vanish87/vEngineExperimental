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

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <VENGINE_API.hpp>
#include <engine.hpp>
#include <vengine/core/game_object.hpp>
#include <vengine/core/iresource.hpp>
#include <vengine/core/element.hpp>
#include <vengine/core/vector.hpp>
#include <vengine/animation/joint.hpp>


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

        struct Vertex
        {
            float3 pos;
            float3 normal;
            float2 uv;
            float4 color;
        };

        template <typename T = Vertex>
        class Mesh_T : public GameObject, public IResource
        {
            // static_assert(std::is_base_of<IElement, T>::value, "T must derived from IElement");
        };
        class VENGINE_API Mesh : public GameObject
        {
            // static_assert(std::is_base_of<IElement, V>::value, "T must derived from IElement");

            public:
                /// \brief Construct a new empty Mesh object
                ///
                Mesh();
                /// \brief Construct a new Mesh object with aiMesh
                /// 
                /// \param mesh aiMesh to load
                Mesh(const aiMesh* mesh);
                virtual ~Mesh();
                void Load(const aiMesh* mesh);
                void UpdateGPUBuffer();

                // Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);


                GraphicsBufferSharedPtr vertex_buffer_;
                GraphicsBufferSharedPtr index_buffer_;

                std::vector<Vertex> vertex_data_;
                std::vector<uint32_t> index_data_;
                std::unordered_map<std::string, Animation::JointSharedPtr> joint_data_;
                GameNodeSharedPtr skeleton_;

                bool loaded = false;
                //vertex
                //index

        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_MESH_HPP */

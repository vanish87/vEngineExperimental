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
#include <unordered_map>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <VENGINE_API.hpp>
#include <engine.hpp>
#include <vengine/core/game_object.hpp>
#include <vengine/core/iresource.hpp>
#include <vengine/core/element.hpp>
#include <vengine/core/vector.hpp>
#include <vengine/animation/bone.hpp>

#include <vengine/data/meta.hpp>


/// A brief namespace description.
namespace vEngine
{
    namespace Core
    {
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.

        struct Vertex
        {
            float3 pos;
            float3 normal;
            float2 uv;
            color color;
            int4 bone_id_0;
            float4 bone_weight_0;
            int4 bone_id_1;
            float4 bone_weight_1;
            constexpr static auto properties()
            {
                return std::make_tuple(
                    property("position", &Vertex::pos),
                    property("normal", &Vertex::normal),
                    property("uv", &Vertex::uv)
                );
            }
        };

        enum class MeshPrimitive
        {
            Cube,
            Sphere,
        };

        template <typename T = Vertex>
        class Mesh_T : public GameObject, public IResource
        {
            // static_assert(std::is_base_of<IElement, T>::value, "T must derived from IElement");
        };
        // template <typename T = Vertex>
        class VENGINE_API Mesh : public GameObject, public IResource
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
                float4x4 AiMatrixToFloat4x4(aiMatrix4x4 mat);

                bool Load(const ResourceDescriptorSharedPtr desc) override;
                ResourceState CurrentState() override;
                ResourceState current_state_ = ResourceState::Unknown;

                // Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);

                Rendering::GraphicsBufferSharedPtr vertex_buffer_;
                Rendering::GraphicsBufferSharedPtr index_buffer_;

                std::vector<Vertex> vertex_data_;
                std::vector<uint32_t> index_data_;
                //TODO Verify if the usage of BoneComponentSharedPtr is a good mesh/bone design
                //GameObject usually does not contain a GameNode object
                std::unordered_map<std::string, Animation::BoneComponentSharedPtr> bone_data_;

                // bool loaded = false;
                //vertex
                //index

                public:
                static void GenerateCube(MeshSharedPtr mesh);
                static MeshSharedPtr Default(const MeshPrimitive primitive = MeshPrimitive::Cube, const int sub_div = 0);

                constexpr static auto properties()
                {
                    return std::tuple_cat(
                        GameObject::properties(),
                        std::make_tuple(
                            property("vertices", &Mesh::vertex_data_),
                            property("indices", &Mesh::index_data_)
                            )
                    );
                }

        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_MESH_HPP */

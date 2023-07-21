
#include <vengine/rendering/d3d11_shader_include.hpp>

#include <fstream>
#include <sstream>
#include <vengine/core/resource_manager.hpp>

namespace vEngine
{
    namespace Rendering
    {

        HRESULT D3D11ShaderInclude::Open(D3D_INCLUDE_TYPE include_type, LPCSTR file_name, LPCVOID parent_data, LPCVOID *data, UINT *bytes)
        {
            UNUSED_PARAMETER(include_type);
            UNUSED_PARAMETER(parent_data);
            *data = nullptr;
            *bytes = 0;

            if (this->file_map_.find(file_name) == this->file_map_.end())
            {
                const auto path = Core::ResourceManager::GetInstance().GetResourceBinFilePath(file_name);

                std::ifstream fin(path);
                if (!fin)
                {
                    PRINT_AND_BREAK("Cannot open hlsl File ");
                    return E_FAIL;
                }
                std::stringstream str_stream;
                str_stream << fin.rdbuf();
                this->file_map_[file_name] = str_stream.str();
                fin.close();
            }

            *data = this->file_map_[file_name].c_str();
            *bytes = static_cast<uint32_t>(this->file_map_[file_name].size());
            return S_OK;
        }
        HRESULT D3D11ShaderInclude::Close(LPCVOID data)
        {
            UNUSED_PARAMETER(data);
            // auto ptr = (char *)(data);
            // delete[] ptr;
            return S_OK;
        }
    }  // namespace Rendering

}  // namespace vEngine

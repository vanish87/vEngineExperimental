#ifndef _VENGINE_RENDERING_D3D11_SHADER_INCLUDE_HPP
#define _VENGINE_RENDERING_D3D11_SHADER_INCLUDE_HPP

#pragma once

#include <unordered_map>

#include <vengine/rendering/d3d11_predeclear.hpp>
#include <vengine/rendering/data_struct.hpp>

namespace vEngine
{
    namespace Rendering
    {
        class D3D11ShaderInclude : public ID3DInclude
        {
            public:
                D3D11ShaderInclude(){};
                ~D3D11ShaderInclude(){};

                HRESULT Open(D3D_INCLUDE_TYPE include_type, LPCSTR file_name, LPCVOID parent_data, LPCVOID *data, UINT *bytes);
                HRESULT Close(LPCVOID data);

            private:
                std::unordered_map<std::string, std::string> file_map_;
        };
    }  // namespace Rendering
}  // namespace vEngine

#endif /* _VENGINE_RENDERING_D3D11_SHADER_INCLUDE_HPP */

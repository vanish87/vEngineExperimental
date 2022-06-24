
#define VENGINE_HLSL
#include "data_cbuffer.hpp"

Texture2D diffuse_tex : register(t0);
// SamplerState diffuse : register(s0)

SamplerState MeshTextureSampler
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};

ps_out ps_main(vs_out input)
{
	// float3 light_pos = float3(1000, 1000, 0);
	float4 ambient_col = 0.1f;
	float4 diffuse_col = float4(1, 1, 1, 1);
	float4 specular_col = float4(0.5f, 0.5f, 0.5f, 1);

	diffuse_col = diffuse_tex.Sample(MeshTextureSampler, input.texcoord);

	float3 pos = input.pos_w;
	float3 normal = normalize(input.normal);

	// float3 light_dir = normalize(light_pos - pos);
	float3 light_dir = normalize(float3(1,1,0));
	float3 view_dir = normalize(camera_pos.xyz - pos);
	float3 reflect_dir = 2 * dot(light_dir, normal) * normal - light_dir;
	// reflect_dir = reflect(light_dir, normal);

	float diffuse = max(0, dot(light_dir, normal));
	float specular = pow(max(dot(reflect_dir, view_dir),0), 10);
	float4 col = ambient_col + (diffuse_col * diffuse  + specular_col * specular);
	// return float4(normal, 1);
	ps_out ret = (ps_out)0;
	ret.color0 = diffuse_col;
	return ret;
}



#define VENGINE_HLSL
#include "data_cbuffer.hpp"


struct vs_out 
{
	float4 position : SV_POSITION; 
	float3 pos_w : POSITION; 
	float3 normal : NORMAL; 
	float4 color : COLOR;
};
float4 ps_main(vs_out input) : SV_TARGET 
{
	// float3 light_pos = float3(1000, 1000, 0);
	float4 ambient_col = 0.4f;
	float4 diffuse_col = float4(1, 1, 1, 1);
	float4 specular_col = 1;

	float3 pos = input.pos_w;
	float3 normal = normalize(input.normal);

	// float3 light_dir = normalize(light_pos - pos);
	float3 light_dir = normalize(float3(1,1,0));
	float3 view_dir = normalize(camera_pos - pos);
	float3 reflect_dir = 2 * dot(light_dir, normal) * normal - light_dir;
	// reflect_dir = reflect(light_dir, normal);

	float diffse = dot(light_dir, normal);
	float specular = pow(max(dot(reflect_dir, view_dir),0), 10);
	float4 col = ambient_col + (diffuse_col * diffse  + specular_col * specular);
	// return float4(normal, 1);
	return col;
}

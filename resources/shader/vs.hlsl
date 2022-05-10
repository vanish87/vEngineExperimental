
#define VENGINE_HLSL
#include "data_cbuffer.hpp"

// #pragma pack_matrix(row_major)

struct vs_in 
{
	float3 position : POSITION;
	float3 normal : NORMAL;
	float2 texcoord : TEXCOORD;
	float4 color : COLOR;
};
struct vs_out 
{
	float4 position : SV_POSITION; 
	float3 pos_w : POSITION; 
	float3 normal : NORMAL;
	float4 color : COLOR;
};
vs_out vs_main(vs_in input) 
{
	vs_out output = (vs_out)0; 
	float4x4 m = local_to_world_matrix;
	float4x4 mv = mul(m, view_matrix);
	float4x4 mvp = mul(mv, proj_matrix);

	float4 pos = float4(input.position, 1);
	float3 normal = input.normal;

	output.position = mul(pos, mvp);
	output.pos_w = mul(pos, m);
	output.normal = mul(normal, (float3x3)m);
	output.color = input.color;
	return output;
}
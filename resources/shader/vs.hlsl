
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
	float4 color : COLOR;
};
vs_out vs_main(vs_in input) 
{
	vs_out output = (vs_out)0; 
	float4 pos = float4(input.position, 1);
	// float4x4 scale = {0.5,0,0,0, 0,0.5,0,0, 0,0,0.5,0, 0,0,0,1};
	// pos = mul(scale, pos);
	pos = mul(pos, local_to_world_matrix);
	pos = mul(pos, view_matrix);
	pos = mul(pos, proj_matrix);
	// pos = mul(proj_matrix, pos);
	output.position = pos;
	output.color = input.color;
	return output;
}
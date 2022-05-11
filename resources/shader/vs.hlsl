
#define VENGINE_HLSL
#include "data_cbuffer.hpp"


vs_out vs_main(vs_in input) 
{
	vs_out output = (vs_out)0; 
	float4x4 m = local_to_world_matrix;
	// m[0][0] = m[1][1] = m[2][2] = 5;
	float4x4 mv = mul(m, view_matrix);
	float4x4 mvp = mul(mv, proj_matrix);

	float4 pos = float4(input.position, 1);
	float3 normal = input.normal;

	output.position = mul(pos, mvp);
	output.pos_w = mul(pos, m).xyz;
	output.normal = mul(normal, (float3x3)m);
	output.color = input.color;
	return output;
}

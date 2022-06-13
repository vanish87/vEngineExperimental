
#define VENGINE_HLSL
#include "data_cbuffer.hpp"


vs_out vs_main(vs_in input) 
{
	vs_out output = (vs_out)0; 
	float4x4 m = local_to_world_matrix;
	float4x4 mv = mul(m, view_matrix);
	float4x4 mvp = mul(mv, proj_matrix);
	float4x4 vp = mul(view_matrix, proj_matrix);

	float4 pos = 0;
	float3 mpos = input.position;
	float3 normal = input.normal;

	for(int i = 0; i < 4; ++i)
	{
		int bid = input.bone_id[i];
		if(bid < 0) continue;
		pos += mul(float4(mpos, 1), bone[bid]) * input.bone_weight[i];
	}

	pos.w = 1;
	if(input.bone_id[0] < 0) 
	{
		pos.xyz = mpos;
		output.position = mul(pos, mvp);
	}
	else
	{
		output.position = mul(pos, vp);
	}

	output.texcoord = input.texcoord;
	output.pos_w = mul(pos, m).xyz;
	output.normal = mul(normal, (float3x3)m);
	output.color = input.color;
	return output;
}

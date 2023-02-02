
#define VENGINE_HLSL
#include "data_cbuffer.hpp"


vs_out main(vs_in input) 
{
	vs_out output = (vs_out)0; 
	float4x4 m = local_to_world_matrix;
	float4x4 mv = mul(m, view_matrix);
	float4x4 mvp = mul(mv, proj_matrix);
	float4x4 vp = mul(view_matrix, proj_matrix);

	float4 pos = 0;
	float3 mpos = input.position;
	float3 normal = 0;
	float3 mnormal = input.normal;

	bool hasBone = false;
	int i = 0;

	for(i = 0; i < 4; ++i)
	{
		int bid = input.bone_id_0[i];
		if(bid < 0) continue;
		hasBone = true;
		pos += mul(float4(mpos, 1), bone[bid]) * input.bone_weight_0[i];
		normal += mul(mnormal, (float3x3)bone[bid]) * input.bone_weight_0[i];
	}
	for(i = 0; i < 4; ++i)
	{
		int bid = input.bone_id_1[i];
		if(bid < 0) continue;
		hasBone = true;
		pos += mul(float4(mpos, 1), bone[bid]) * input.bone_weight_1[i];
		normal += mul(mnormal, (float3x3)bone[bid]) * input.bone_weight_1[i];
	}

	pos.w = 1;
	if(!hasBone)
	{
		pos.xyz = mpos;
		output.position = mul(pos, mvp);
		output.pos_w = mul(pos, m).xyz;
		output.normal = mul(mnormal, (float3x3)m);
	}
	else
	{
		output.position = mul(pos, vp);
		output.pos_w = pos.xyz;
		output.normal = normal;
	}

	output.texcoord = input.texcoord;
	output.color = input.color;
	return output;
}

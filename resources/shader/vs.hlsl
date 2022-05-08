
#define VENGINE_HLSL
#include "data_cbuffer.hpp"

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
	output.position = float4(input.position,1);
	output.color = input.color;
	return output;
}
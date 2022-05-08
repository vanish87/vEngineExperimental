
#define VENGINE_HLSL
#include "data_cbuffer.hpp"

struct vs_out 
{
	float4 position : SV_POSITION; 
	float4 color : COLOR;
};
float4 ps_main(vs_out input) : SV_TARGET 
{
	return input.color;
}

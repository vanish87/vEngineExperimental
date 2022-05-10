#ifndef _VENGINE_RENDERING_DATA_CBUFFER_HPP
#define _VENGINE_RENDERING_DATA_CBUFFER_HPP


#if defined(VENGINE_HLSL)

#define struct_def cbuffer
#define register_def(r)  :register(r)
#define semantics_def(s) :s

#else

#pragma once
#define struct_def struct
#define register_def(r) 
#define semantics_def(s) 

#include <engine.hpp>
#include <vengine/core/matrix.hpp>
using namespace vEngine::Math;

#endif

static const int vEngineConstantBufferPerCamera = 0;
static const int vEngineConstantBufferPerObject = 1;

struct vs_in 
{
	float3 position semantics_def(POSITION);
	float3 normal semantics_def(NORMAL);
	float2 texcoord semantics_def(TEXCOORD0);
	float4 color semantics_def(COLOR);
};
struct vs_out 
{
	float4 position semantics_def(SV_POSITION); 
	float3 pos_w semantics_def(POSITION); 
	float3 normal semantics_def(NORMAL);
	float4 color semantics_def(COLOR);
};
struct ps_out
{
	float4 color0 semantics_def(SV_TARGET0);
};

struct_def vEngineCameraConstantBuffer register_def(b0)
{
	float4 camera_pos;
	float4x4 view_matrix;
	float4x4 proj_matrix;
};
struct_def vEngineObjectConstantBuffer register_def(b1)
{
	float4x4 local_to_world_matrix;
};

#endif /* _VENGINE_RENDERING_DATA_CBUFFER_HPP */

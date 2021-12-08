
#include <vengine/rendering/d3d11_render_engine.hpp>

void D3D11RenderEngine::TestFunc(){

};

void D3D11RenderEngine::Render(){

};
RenderEngine* Create(void)
{
	return new D3D11RenderEngine();
};

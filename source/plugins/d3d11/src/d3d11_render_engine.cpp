
#include <iostream>
#include <vengine/rendering/d3d11_render_engine.hpp>

namespace vEngine
{
    namespace Rendering
    {

        void D3D11RenderEngine::TestFunc(){

        };

        void D3D11RenderEngine::CreateRenderWindow(){

        };
        void D3D11RenderEngine::Render(){

        };

    }  // namespace Rendering
}  // namespace vEngine

extern "C" 
{
     void CreateRenderEngine(std::unique_ptr<vEngine::Rendering::RenderEngine>& ptr)
    {
        std::cout << "D3D11" << std::endl;
        ptr = std::make_unique<vEngine::Rendering::D3D11RenderEngine>();
    }
}
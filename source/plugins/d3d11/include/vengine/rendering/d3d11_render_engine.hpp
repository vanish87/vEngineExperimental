
#include <vengine/rendering/render_engine.hpp>
#include <windows.h>


class D3D11RenderEngine : public RenderEngine
{
	public:
	void TestFunc();
	void Render() override;

};
extern "C" 
{
    // __declspec(dllexport) RenderEngine* __cdecl Create()
    // {
    //     return new D3D11RenderEngine();
    // };
}
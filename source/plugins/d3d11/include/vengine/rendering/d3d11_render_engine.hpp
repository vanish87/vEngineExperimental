
#include <vengine/rendering/render_engine.hpp>
class RENDERING_API D3D11RenderEngine : public RenderEngine
{
	public:
	void TestFunc();
	void Render() override;

};
extern "C" 
{
    __declspec(dllexport) RenderEngine* Create(void);
}

#include <vengine/rendering/render_engine.hpp>
class D3D11RenderEngine : public RenderEngine
{
	public:
	void TestFunc();
	void Render() override;

};
extern "C" 
{
    __declspec(dllexport) int Create(void);
}

#include <vengine/rendering/render_engine.hpp>
namespace vEngine
{
    namespace Rendering
    {
        class D3D11RenderEngine : public RenderEngine
        {
            public:
                void TestFunc();
                void Render() override;
        };

        extern "C" {
            RENDERING_API RenderEngine* Create(void);
        }
    }  // namespace Rendering
}  // namespace vEngine
#ifndef _VENGINE_RENDERING_IRENDERER_HPP
#define _VENGINE_RENDERING_IRENDERER_HPP

namespace vEngine
{
    namespace Rendering
    {
        Interface IRenderer
        {
        public:
            virtual bool UpdateRenderable() = 0;
            virtual void Render() = 0;
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_RENDERING_IRENDERER_HPP */

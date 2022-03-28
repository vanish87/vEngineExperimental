#ifndef _VENGINE_CORE_IRENDERER_HPP
#define _VENGINE_CORE_IRENDERER_HPP

namespace vEngine
{
    namespace Core
    {
        Interface IRenderer
        {
        public:
            virtual void Render() = 0;
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_IRENDERER_HPP */

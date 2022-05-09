#ifndef _VENGINE_CORE_ICOMPONENT_HPP
#define _VENGINE_CORE_ICOMPONENT_HPP

/// A brief namespace description.
namespace vEngine
{
    namespace Core
    {
        Interface VENGINE_API IComponent
        {
        public:
            virtual void Update(GameNodeSharedPtr parent)
            {
                UNUSED_PARAMETER(parent);
            };

        protected:
            virtual ~IComponent(){};
        };
    }  // namespace Core
}  // namespace vEngine
#endif /* _VENGINE_CORE_ICOMPONENT_HPP */

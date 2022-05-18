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
            virtual GameNodeSharedPtr Owner() = 0;

            virtual void OnInit(){};
            virtual void OnDeinit(){};
            virtual void OnEnable(){};
            virtual void OnDisable(){};
            virtual void OnUpdate(GameNodeSharedPtr parent)
            {
                UNUSED_PARAMETER(parent);
            };

        protected:
            virtual ~IComponent(){};
        };
    }  // namespace Core
}  // namespace vEngine
#endif /* _VENGINE_CORE_ICOMPONENT_HPP */

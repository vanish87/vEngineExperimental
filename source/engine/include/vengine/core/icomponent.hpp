/// \file icomponent.hpp
/// \brief Head file for Component Interface
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

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
            IComponent()
            {
                this->OnInit();
            };
            virtual ~IComponent()
            {
                this->OnDeinit();
            };

        public:
            virtual GameNodeSharedPtr Owner() = 0;
            virtual bool Enabled() const = 0;
            virtual void SetEnable(const bool enable) = 0;

            virtual void OnInit(){};
            virtual void OnDeinit(){};
            virtual void OnEnable(){};
            virtual void OnDisable(){};
            virtual void OnUpdate(){};
        };
    }  // namespace Core
}  // namespace vEngine
#endif /* _VENGINE_CORE_ICOMPONENT_HPP */

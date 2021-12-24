#ifndef _IAPPLICATION_HPP
#define _IAPPLICATION_HPP

#include <CORE_API.h>

#include <vengine/core/interface.hpp>
#include <vengine/core/predeclear.hpp>
#include <compiler_setting.hpp>

namespace vEngine
{
    namespace Core
    {
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        Interface CORE_API IApplication
        {
        public:
            virtual void Init() = 0;
            virtual void Run() = 0;

		protected:
            WindowPtr window_;

        private:
            virtual void OnCreate() = 0;
            virtual void OnUpdate() = 0;
            virtual void OnDestory() = 0;

            virtual void SetupWindow() = 0;

        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _IAPPLICATION_HPP */

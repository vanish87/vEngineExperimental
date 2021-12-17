#ifndef _IAPPLICATION_HPP
#define _IAPPLICATION_HPP

#include <CORE_API.h>
#include <vengine/core/interface.hpp>
#include <vengine/core/predeclear.hpp>

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
			/// \brief a function comment
			/// 
			/// \param i input
			void TestFuction(int i);
			virtual void Run() = 0;

			private:

			Window* window_;

		};
	}
}


#endif /* _IAPPLICATION_HPP */

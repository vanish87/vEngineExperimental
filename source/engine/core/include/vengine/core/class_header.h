/// \file class_header.h
/// \brief Head file for class Ctest.
/// 
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <iostream>

///A brief namespace description. 
namespace MyNamespace
{
   /// \brief A brief class description. 
   /// 
   /// A detailed class description, it
   /// should be 2 lines at least.
   class  MyClass
   {
        public:
            /// \brief brief constructor description. 
            MyClass();

            /// class variable description
            int PublicVariable; 
            
        public:
            /// \brief A brief function description. 
            ///
            /// \param p1 Description for p1.
            /// \param p2 Description for p2.
            /// \return Description for return value.
            int GetVariable(int p1, float p2);
   };
}
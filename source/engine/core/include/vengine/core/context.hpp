#ifndef _VENGINE_CORE_CONTEXT_HPP
#define _VENGINE_CORE_CONTEXT_HPP

#pragma once
namespace vEngine
{
    namespace Core
    {
        class Context
        {
            public:
                void Setup();

                void RegisterAppInstance();
                // RenderFactory& RenderFactoty();

			public:
				bool IsQuit();
				void SetQuit(bool value);

				private:
				bool quit_;
        };

    }  // namespace Core

}  // namespace vEngine

#endif /* _VENGINE_CORE_CONTEXT_HPP */

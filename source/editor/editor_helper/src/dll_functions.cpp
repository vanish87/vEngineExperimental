#include <vengine/editor/dll_functions.hpp>

#include <vengine/core/context.hpp>

extern "C" 
{
	using namespace vEngine::Core;

	void Context_Init(void* hwnd)
	{
		UNUSED_PARAMETER(hwnd);
		PRINT("Context_Init");

		Configure configure;
		configure.graphics_configure.render_plugin_name = "d3d11_rendering_plugin";
		Context::GetInstance().ConfigureWith(configure);

	}

	void Context_Deinit()
	{
		PRINT("Context_Deinit");
	}
}
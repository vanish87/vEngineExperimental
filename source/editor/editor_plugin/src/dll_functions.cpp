#include <vengine/core/context.hpp>
#include <vengine/editor/dll_functions.hpp>
#include <vengine/rendering/render_engine.hpp>

namespace vEngine
{
    namespace Editor
    {
        using namespace vEngine::Core;

        EditorApp editor_app;
        void EditorApp::EditorInit()
        {
            this->Init();
        }
        void EditorApp::EditorDeinit()
        {
            this->Deinit();
        }

        void EditorApp::EditorUpdate()
        {
            this->Update();
        }
    }  // namespace Editor

}  // namespace vEngine
extern "C" {
    using namespace vEngine::Core;
    using namespace vEngine::Editor;
    void Context_Init(void* hwnd)
    {
        CHECK_ASSERT_NOT_NULL(hwnd);

        PRINT("Context_Init");

        Configure configure;
        configure.graphics_configure.render_plugin_name = "d3d11_rendering_plugin";
        configure.graphics_configure.wnd = hwnd;
        Context::GetInstance().SetConfigure(configure);

        editor_app.EditorInit();
    }
    void Context_Update()
    {
        editor_app.EditorUpdate();
    }

    void Context_Deinit()
    {
        editor_app.EditorDeinit();
    }
}
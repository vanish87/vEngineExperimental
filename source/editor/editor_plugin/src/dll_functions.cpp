#include <vengine/editor/dll_functions.hpp>
#include <vengine/core/context.hpp>
#include <vengine/core/scene_manager.hpp>

namespace vEngine
{
    namespace Editor
    {
        using namespace vEngine::Core;

        std::shared_ptr<EditorApp> editor_app;
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

        void EditorApp::OnInit()
        {
            SceneManager::GetInstance().Load("boblampclean.json");
        }
    }  // namespace Editor

}  // namespace vEngine
extern "C"
{
    using namespace vEngine::Core;
    using namespace vEngine::Editor;
    void Context_Init(void* hwnd)
    {
        VE_ASSERT_PTR_NOT_NULL(hwnd);

        VE_INFO("Context_Init");

        Configure configure;
        configure.graphics_configure.render_plugin_name = "d3d11_rendering_plugin";
        configure.graphics_configure.wnd = hwnd;
        Context::GetInstance().SetConfigure(configure);

        editor_app = std::make_shared<EditorApp>();
        editor_app->EditorInit();
    }
    void Context_Update()
    {
        editor_app->EditorUpdate();
    }

    void Context_Deinit()
    {
        editor_app->EditorDeinit();
    }
}
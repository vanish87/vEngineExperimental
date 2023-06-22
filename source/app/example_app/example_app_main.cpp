#include <engine.hpp>
#include <version.hpp>
#include <vengine/core/application.hpp>
#include <vengine/core/context.hpp>
#include <vengine/core/scene_manager.hpp>

using namespace vEngine::Core;

/// Namespace for example applications
namespace Example
{
    /// \brief A general example of user application
    class ExampleApp : public Application
    {
        private:
            /// \brief user function for create
            /// 
            void OnInit() override
            {
                PRINT("User Create");

                SceneManager::GetInstance().Load("boblampclean.json");

            }
            /// \brief user function for update
            ///
            /// Will be call at const seconds
            /// vEngine::TIME_PER_UPDATE
            void OnUpdate() override
            {
            }
            /// \brief user function for destory
            void OnDeinit() override
            {
                PRINT("User Destory");
            }
    };
}  // namespace Example

int main(int argc, char* argv[])
{
    UNUSED_PARAMETER(argc);
    UNUSED_PARAMETER(argv);

    std::cout << "Version " + std::string(Version) << std::endl;

    Configure configure;
    configure.graphics_configure.width = 1280;
    configure.graphics_configure.height = 720;
    #ifdef VENGINE_PLATFORM_WINDOWS
    configure.graphics_configure.render_plugin_name = "d3d11_rendering_plugin";
    #else
    configure.graphics_configure.render_plugin_name = "opengl_rendering_plugin";
    #endif

    Context::GetInstance().SetConfigure(configure);

    auto app = std::make_shared<Example::ExampleApp>();
    app->Run();
}

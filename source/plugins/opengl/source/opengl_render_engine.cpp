#include <vengine/rendering/opengl_render_engine.hpp>

#include <vengine/core/application.hpp>
#include <vengine/core/context.hpp>
#include <OPENGL_RENDERING_PLUGIN_API.hpp>

// Test include
#include <glad/linmath.h>
namespace vEngine
{
    namespace Rendering
    {
        using namespace vEngine::Core;

        static void error_callback(int error, const char* description)
        {
            UNUSED_PARAMETER(error);
            CHECK_AND_ASSERT(false, description);
        }

        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            UNUSED_PARAMETER(scancode);
            UNUSED_PARAMETER(mods);
            if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            {
                glfwSetWindowShouldClose(window, GLFW_TRUE);
            }
        }

        void OpenGLRenderEngine::Init()
        {
            const auto config = Context::GetInstance().CurrentConfigure();
            auto app_name = config.app_name;
            auto width = config.graphics_configure.width;
            auto height = config.graphics_configure.height;

            glfwSetErrorCallback(error_callback);

            if (!glfwInit()) exit(EXIT_FAILURE);

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

            window = glfwCreateWindow(width, height, app_name.c_str(), NULL, NULL);
            if (!window)
            {
                glfwTerminate();
                exit(EXIT_FAILURE);
            }

            glfwSetKeyCallback(window, key_callback);

            glfwMakeContextCurrent(window);
            gladLoadGL(glfwGetProcAddress);
            glfwSwapInterval(1);

            this->InitPipeline();
        }

        void OpenGLRenderEngine::Update()
        {
            if (glfwWindowShouldClose(window))
            {
                Context::GetInstance().QuitApplication();
                return;
            }
            int width, height;
            glfwGetFramebufferSize(window, &width, &height);

            glViewport(0, 0, width, height);
            glClear(GL_COLOR_BUFFER_BIT);

            this->DebugTriangleDraw();

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        void OpenGLRenderEngine::Deinit()
        {
            glfwDestroyWindow(window);
            glfwTerminate();
        }
        void OpenGLRenderEngine::PrintInfo()
        {
            std::cout << "OpenGL" << std::endl;
        }

        static const struct
        {
                float x, y;
                float r, g, b;
        } vertices[3] = {{-0.6f, -0.4f, 1.f, 0.f, 0.f}, {0.6f, -0.4f, 0.f, 1.f, 0.f}, {0.f, 0.6f, 0.f, 0.f, 1.f}};

        static const char* vertex_shader_text =
            "#version 110\n"
            "uniform mat4 MVP;\n"
            "attribute vec3 vCol;\n"
            "attribute vec2 vPos;\n"
            "varying vec3 color;\n"
            "void main()\n"
            "{\n"
            "    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
            "    color = vCol;\n"
            "}\n";

        static const char* fragment_shader_text =
            "#version 110\n"
            "varying vec3 color;\n"
            "void main()\n"
            "{\n"
            "    gl_FragColor = vec4(color, 1.0);\n"
            "}\n";
        void OpenGLRenderEngine::InitPipeline()
        {
            glGenBuffers(1, &vertex_buffer);
            glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            vertex_shader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
            glCompileShader(vertex_shader);

            fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
            glCompileShader(fragment_shader);

            program = glCreateProgram();
            glAttachShader(program, vertex_shader);
            glAttachShader(program, fragment_shader);
            glLinkProgram(program);

            mvp_location = glGetUniformLocation(program, "MVP");
            vpos_location = glGetAttribLocation(program, "vPos");
            vcol_location = glGetAttribLocation(program, "vCol");

            glEnableVertexAttribArray(vpos_location);
            glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*)0);
            glEnableVertexAttribArray(vcol_location);
            glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*)(sizeof(float) * 2));
        }

        void OpenGLRenderEngine::DebugTriangleDraw()
        {
            float ratio;
            int width, height;

            glfwGetFramebufferSize(window, &width, &height);
            ratio = width / (float)height;
            mat4x4 m, p, mvp;
            mat4x4_identity(m);
            mat4x4_rotate_Z(m, m, (float)glfwGetTime());
            mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
            mat4x4_mul(mvp, p, m);

            glUseProgram(program);
            glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)mvp);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }
        void OpenGLRenderEngine::DeinitPipeline() {}
    }  // namespace Rendering
}  // namespace vEngine

extern "C" {
    OPENGL_RENDERING_PLUGIN_API void CreateRenderEngine(std::unique_ptr<vEngine::Rendering::RenderEngine>& ptr)
    {
        ptr = std::make_unique<vEngine::Rendering::OpenGLRenderEngine>();
    }
    // it is not used but just keep it for reference
    // ptr.reset is be called on context
    OPENGL_RENDERING_PLUGIN_API void DestoryRenderEngine(std::unique_ptr<vEngine::Rendering::RenderEngine>& ptr)
    {
        ptr.reset();
    }
}

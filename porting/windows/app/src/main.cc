#include "GLES2/gl2.h"
#include "GLFW/glfw3.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "bunny/engine.h"

using namespace bunny;

const char *TAG = "bunny::native";

static GLFWwindow *window = nullptr;

static ImVec2 windowSize = {1280, 720};

static float fontDefaultSize = windowSize.y / 24.0f;

void glfw_error_callback(int error_code, const char *description);

int main() {
    bunny::Engine::GetInstance();

    // Init glfw
    TAG = "bunny::native::glfw";
    glfwSetErrorCallback(glfw_error_callback);
    if (glfwInit() != GLFW_TRUE) {
        LOGF("failed to init glfw!");
    }
    LOGI("glfw initialized.");

    // GL ES 2.0 + GLSL 100
    const char *glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    // Create window
    window = glfwCreateWindow(int(windowSize.x), int(windowSize.y), "bunny", nullptr, nullptr);
    if (window == nullptr) {
        LOGF("failed to create window!");
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
    LOGI("window created.");

    // Setup Dear ImGui context
    TAG = "bunny::native::imgui";
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls
    io.IniFilename = nullptr;

    // Setup font
    LOGI("loading font textures ...");
    io.Fonts->AddFontFromFileTTF(
            (FileSystem::Assets::AbsolutePath("fonts/YaHei Consolas Hybrid 1.12.ttf")).c_str(),
            fontDefaultSize,
            nullptr, io.Fonts->GetGlyphRangesChineseFull());
    io.Fonts->Build();

    // Setup Dear ImGui style
    ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    LOGI("imgui initialized.");

    // Our state
    bool show_demo_window = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    Image avatarImage(FileSystem::GetInstance().CachePath() + "/images/avatar2.jpg");

    glfwShowWindow(window);
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        {
            ImGui::Begin("main", nullptr,
                         ImGuiWindowFlags_NoMove
                         | ImGuiWindowFlags_NoResize
                         | ImGuiWindowFlags_NoTitleBar
                         | ImGuiWindowFlags_NoBringToFrontOnFocus);
            ImGui::SetWindowPos(ImVec2(0, 0));
            ImGui::SetWindowSize(windowSize);
            if (ImGui::IsWindowHovered()) {
                ImGui::Image(avatarImage.GetTexture(), {300, 300}, {1, 0}, {0, 1});
            } else {
                ImGui::Image(avatarImage.GetTexture(), {300, 300}, {0, 0}, {1, 1});
            }
            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w,
                     clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    TAG = "bunny::native::imgui";
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    LOGI("imgui destroyed.");

    TAG = "bunny::native::glfw";
    glfwDestroyWindow(window);
    LOGI("window destroyed.");
    glfwTerminate();
    LOGI("glfw destroyed.");
    return 0;
}

void glfw_error_callback(int error_code, const char *description) {
    TAG = "bunny::native::glfw";
    LOGE("glfw error[%d]: %s", error_code, description);
}
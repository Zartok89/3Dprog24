#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui_impl_opengl3.h"
#include "utility/Logger.h"

Window::Window(std::string name, /*Scene* scene, */int width, int height)
{
    mName = name;
    mWidth = width;
    mHeight = height;
}

Window::~Window()
{
}

void Window::InitializingWindow()
{
	LOG_INFO("Window::Init");
    mGLFWWindow = glfwCreateWindow(mWidth, mHeight, mName.c_str(), NULL, NULL);
    if (mGLFWWindow == NULL)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create glfw window");
    }
    glfwMakeContextCurrent(mGLFWWindow);
	glfwSwapInterval(1); // Enable vsync

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
       std::runtime_error("Failed to initialize glad");
    }

	IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

	ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(mGLFWWindow, false);
    ImGui_ImplOpenGL3_Init("#version 130");
}

void Window::RegisterCallback()
{
        glfwSetFramebufferSizeCallback(mGLFWWindow, [](GLFWwindow* window, int width, int height) {
        auto windowApplication = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
        if (windowApplication)
        {
            windowApplication->FramebufferSizeCallback(window, width, height);
            windowApplication->SetWidth(width);
            windowApplication->SetHeight(height);
        }
        });

    glfwSetCursorPosCallback(mGLFWWindow, [](GLFWwindow* window, double xpos, double ypos) {
        auto windowApplication = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
        if (windowApplication) windowApplication->MouseMoveCallback(window, xpos, ypos);
        });
    glfwSetMouseButtonCallback(mGLFWWindow, [](GLFWwindow* window, int button, int action, int mods) {
        auto windowApplication = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
        if (windowApplication) windowApplication->MouseButtonCallback(window, button, action, mods);
        });

    glfwSetScrollCallback(mGLFWWindow, [](GLFWwindow* window, double xoffset, double yoffset) {
        auto windowApplication = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
        if (windowApplication) windowApplication->MouseScrollCallback(window, xoffset, yoffset);
        });

    glfwSetKeyCallback(mGLFWWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        auto windowApplication = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
        if (windowApplication) windowApplication->KeyCallback(window, key, scancode, action, mods);
        });

    // Store pointer so it can be accessed in callbacks
    glfwSetWindowUserPointer(mGLFWWindow, this);
}

bool Window::LoadContent()
{
    LOG_INFO("Window::LoadContent");
    return true;
}

void Window::StartFrame()
{
	glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::Update(float dt)
{

}

void Window::Render(float dt)
{
}

void Window::EndFrame()
{
	ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(mGLFWWindow);
}

bool Window::IsClosed()
{
    return glfwWindowShouldClose(mGLFWWindow);
}

void Window::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	LOG_INFO("Window::FramebufferSizeCallback");
    glViewport(0, 0, width, height);
}

void Window::MouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (ImGui::GetIO().WantCaptureMouse) return;
}

void Window::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    LOG_INFO("Window::MouseButtonCallback");

    ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
    if (ImGui::GetIO().WantCaptureMouse) return;
}

void Window::MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	LOG_INFO("Window::MouseScrollCallback");

    ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);
    if (ImGui::GetIO().WantCaptureMouse) return;
}

void Window::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	LOG_INFO("Window::KeyCallback");

    ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
}

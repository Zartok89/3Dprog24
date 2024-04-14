#include "Application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "utility/Logger.h"


Application* Application::GetApplication()
{
    static Application* application = new Application;
    return application;
}

void Application::InitializingApplication()
{
    InitializeGLFW();
    //mWindow.InitializingWindow(); 
}

void Application::InitializeGLFW()
{
	LOG_INFO("Application::InitializeGLFW");
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Application::LoadProjectContent()
{
}

void Application::Run()
{
	InitializingApplication();

    //glfwTerminate();
}

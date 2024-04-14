#pragma once
#include <string>
#include <imgui_impl_glfw.h>

class Scene;

class Window
{
public:
    Window(std::string name, /*Scene* scene, */int width, int height); // Default constructor of Window
    ~Window(); // Deconstructing window and calls these for GLFW and ImGui as well

    /*
     * Initializing all function and contents before rendering
     */
    void InitializingWindow(); // Creating the actual window
    void RegisterCallback(); // Registering the callbaks to the OS
    bool LoadContent(); // Check whether the scene content is loaded or not
   // void SetScene(Scene* scene);

    /*
     * The GLFW while loop sequence
     */
	void StartFrame(); // What should happend at the first frame
    void Update(float dt); // Updates all the scene object based on deltaTime
    void Render(float dt); // Renders all the scene object based on deltaTime
    void EndFrame(); // What should happend at the last frame of the while cycle

    /*
     * After the GLFW while loop sequence
     */
	bool IsClosed(); // Whether the while loop sequence should close or not based on the active window 


    /*
     * Callback functions
     */
	void FramebufferSizeCallback(class GLFWwindow* window, int width, int height);
    void MouseMoveCallback(class GLFWwindow* window, double xpos, double ypos);
    void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    void MouseScrollCallback(class GLFWwindow* window, double xoffset, double yoffset);
    void KeyCallback(class GLFWwindow* window, int key, int scancode, int action, int mods);

    /*
     * Setter function related to the window class
     */
    void SetWidth(int width) { mWidth = width; }
    void SetHeight(int height) { mHeight = height; }

    /*
     * Getter function related to the window class
     */
    int GetWidth() const { return mWidth; }
    int GetHeight() const { return mHeight; }
    class GLFWwindow* GetGLFWWindow() const { return mGLFWWindow; };

private:
    std::string mName;
    int mWidth{1920}, mHeight{1080};
    
    Scene* mScene{nullptr};
    class GLFWwindow* mGLFWWindow{ nullptr };
};

#pragma once
#include <string>

#include "camera/Camera.h"

class Scene
{

public:
	explicit Scene(const std::string& name); // A constructor which wont allow for implicit conversions
    virtual ~Scene(); // A virtual deconstructor which lets the objects inheriting override the function

    Scene(const Scene&) = delete; // Delete copy constructor
    Scene& operator=(const Scene&) = delete; // Delete copy assignment operator
    Scene(Scene&&) = delete;  // Delete move constructor
    Scene& operator=(Scene&&) = delete; // Delete move assignment operator

    virtual void LoadContent(); // Loading all content related to the spesific overrided scene
    virtual void UnloadContent(); // Unloading all content related to the spesific overrided scene
	//void UpdateSceneGraph(Actor* actor, float dt, Transform globalTransform = Transform{});
    //void RenderSceneGraph(Actor* actor, float dt, Transform globalTransform = Transform{});
    void UpdatingScene(float dt); // Updating transforms in the scene using deltaTime
    void RenderingScene(float dt); // Rendering the actors in the scene using deltaTime

    void FramebufferSizeCallback(class Window* window, int width, int height); // Window callbacks related to the spesific scene
    void MouseMoveCallback(class Window* window, double xpos, double ypos); // Mouse movement callbacks related to the spesific scene
    void MouseButtonCallback(class Window* window, int button, int action, int mods); // Mouse button callbacks related to the spesific scene
    void MouseScrollCallback(class Window* window, double xoffset, double yoffset); // Mouse scroll callbacks related to the spesific scene
    void KeyCallback(class Window* window, int key, int scancode, int action, int mods); // Keyboard key callbacks related to the spesific scene

    Camera mSceneCamera{ "SceneCamera" };
};
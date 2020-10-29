#include "System/window.h"
#include "System/logging.h"
#include "System/Input.h"
#include "System/ResourceManager.h"
#include "System/EventSystem.h"


Window::Window()
{
    EventBus::Subscribe(this, &Window::OnUpdate);
    EventBus::Subscribe(this, &Window::OnInit);
}

void Window::OnInit(const ApplicationInitEvent* IE)
{
    window  = glfwCreateWindow(IE->width, IE->height, IE->title, NULL, NULL);

    if (window == NULL)
    {
        Logger::PrintError("Failed to create GLFW window\n");
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Logger::PrintError("Failed to initialize GLAD\n");
        return;
    }

    glViewport(0, 0, IE->width, IE->height);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ResourceManager::LoadResources();

    ViewBounds bounds = 
    { 
        ((-aspectRatio.x / 10.0f) * scaleFactor)/2,
        ((aspectRatio.x / 10.0f) * scaleFactor)/2, 
        ((-aspectRatio.y / 10.0f) * scaleFactor)/2, 
        ((aspectRatio.y / 10.0f) * scaleFactor)/2 
    };

    view = new View (bounds);
    DE = new DrawEvent(view);

    sceneManager = new SceneManager;
}

void Window::GetWindowSize(int* width, int* height)
{
    glfwGetWindowSize(window, width, height);
}

void Window::OnUpdate(const UpdateEvent* UE)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);
}

void Window::RenderWindow()
{
    EventBus::Publish(DE);
}

void Window::Close()
{
    Logger::PrintMessage("Window closing.", 1);
    sceneManager->GetCurrentScene()->End();
    delete sceneManager;
    delete view;
    ResourceManager::UnloadResources();
    Logger::PrintMessage("Window closed.", 1);
}

void Window::PollWindowEvents()
{
    Input::Update();
    glfwPollEvents();
}

void Window::FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

View* Window::GetView()
{
    return view;
}

SceneManager* Window::GetSceneManager() const
{
    return sceneManager;
}

GLFWwindow* Window::GetGLFWWindow()
{
    return window;
}



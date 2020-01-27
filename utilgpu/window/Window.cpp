#include "Window.h"

#include <cassert>
#include <iostream>
#include <map>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <utilgpu/gl/Renderer.h>

namespace util
{
namespace
{
std::map<GLFWwindow*, Window*> windows;

void ErrorCallback(int, const char* description)
{
    std::cout << "GLFW Error: " << description << std::endl;
}

void onResize(GLFWwindow* window, int width, int height)
{
    assert(width >= 0 && height >= 0);
    windows[window]->resize(width, height);
}

void onKeyPress(GLFWwindow* window, int key, int, int action, int mods)
{
    windows[window]->keyPress(key, action, mods);
}
}  // namespace

Window::Window()
    : m_window{nullptr}, m_viewport{640, 480}, m_fileResolution{0, 0}
{
    setFileResolution(1920, 1080);
    glfwSetErrorCallback(ErrorCallback);
    glfwInit();
    glfwWindowHint(GLFW_AUTO_ICONIFY, 0);
}

Window::~Window()
{
    glfwTerminate();
    if (m_window != nullptr)
    {
        windows.erase(m_window);
    }
}

void Window::requestGLVersion(const int& major, const int& minor)
{
    if (m_window)
    {
        std::cout << "GL Version should be requested before window creation."
                  << std::endl;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
}

void Window::MSAASamples(const unsigned int& samples)
{
    if (m_window)
    {
        std::cout << "MSAA should be requested before window creation."
                  << std::endl;
    }
    glfwWindowHint(GLFW_SAMPLES, samples);
}

void Window::alwaysRedraw(bool alwaysRedraw)
{
    m_alwaysRedraw = alwaysRedraw;
}

int Window::init(const std::string& title, const bool& fullscreen)
{
    auto monitor = fullscreen ? glfwGetPrimaryMonitor() : nullptr;
    if (fullscreen)
    {
        const auto mode = glfwGetVideoMode(monitor);
        m_viewport = {0, 0, static_cast<unsigned int>(mode->width),
                      static_cast<unsigned int>(mode->height)};
    }
    m_window = glfwCreateWindow(m_viewport.width, m_viewport.height,
                                title.c_str(), monitor, nullptr);

    if (!m_window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(m_window);
    windows[m_window] = this;

    return 0;
}

void (*(*(getGLProcAddressPointer()))(const char*))()
{
    return glfwGetProcAddress;
}

void Window::initAfterGL()
{
    glfwSetWindowSizeCallback(m_window, onResize);
    glfwSetKeyCallback(m_window, onKeyPress);
}

void Window::setRenderer(std::unique_ptr<util::Renderer> renderer)
{
    m_renderer = std::move(renderer);
    m_renderer->init();
}

void Window::setFileResolution(const unsigned int& width,
                               const unsigned int& height)
{
    m_fileResolution = {width, height};
}

util::Renderer* Window::renderer()
{
    return m_renderer.get();
}

void Window::keyPress(int key, int action, int mods)
{
    if (key == 'R' && action == GLFW_PRESS && mods == 0)
    {
        m_renderer->reload();
    }
    else if (key == 'S' && action == GLFW_PRESS && mods == 0)
    {
        m_renderer->renderToFile(m_fileResolution);
    }
    else if (key == 'F' && action == GLFW_PRESS && mods == 0)
    {
        m_renderer->toggleFrameTimeDisplay();
    }
    else if (key == 'Q' && action == GLFW_PRESS && mods == GLFW_MOD_CONTROL)
    {
        glfwSetWindowShouldClose(m_window, 1);
    }
}

void Window::resize(const unsigned int& width, const unsigned int& height)
{
    m_viewport = {0, 0, width, height};
    util::viewport::set(m_viewport);
}

void Window::loop()
{
    while (!glfwWindowShouldClose(m_window))
    {
        m_renderer->render(m_viewport);
        glfwSwapBuffers(m_window);
        if (m_alwaysRedraw)
        {
            glfwPollEvents();
        }
        else
        {
            glfwWaitEvents();
        }
    }
}
}  // namespace util

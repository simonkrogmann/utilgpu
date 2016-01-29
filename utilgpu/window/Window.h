#pragma once

#include <string>
#include <memory>

#include <utilgpu/gl/viewport.h>
#include <utilgpu/gl/Renderer.h>

struct GLFWwindow;

namespace util
{
class Window
{
public:
    Window();
    ~Window();

    void requestGLVersion(const int& major, const int& minor);
    int init(const std::string& title, const bool& fullscreen);
    void initAfterGL();
    void setRenderer(std::unique_ptr<util::Renderer> renderer);
    util::Renderer* renderer();
    void keyPress(int key, int action, int mods);
    void resize(const unsigned int& width, const unsigned int& height);
    void setFileResolution(const unsigned int& width,
                           const unsigned int& height);
    void loop();

private:
    GLFWwindow* m_window;
    std::unique_ptr<util::Renderer> m_renderer;
    util::viewport::Viewport m_viewport;
    util::viewport::Viewport m_fileResolution;
};
}

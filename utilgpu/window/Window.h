#pragma once

#include <memory>
#include <string>

#include <utilgpu/gl/viewport.h>

struct GLFWwindow;

namespace util
{
class Renderer;

class Window
{
public:
    Window();
    ~Window();

    // call before creating the window
    void requestGLVersion(const int& major, const int& minor);
    void MSAASamples(const unsigned int& samples);
    void alwaysRedraw(bool alwaysRedraw);

    int init(const std::string& title, const bool& fullscreen);
    void initAfterGL();
    void setRenderer(std::unique_ptr<Renderer> renderer);
    Renderer* renderer();
    void keyPress(int key, int action, int mods);
    void resize(const unsigned int& width, const unsigned int& height);
    void setFileResolution(const unsigned int& width,
                           const unsigned int& height);
    void loop();

private:
    GLFWwindow* m_window;
    std::unique_ptr<Renderer> m_renderer;
    viewport::Viewport m_viewport;
    viewport::Viewport m_fileResolution;
    bool m_alwaysRedraw = true;
};
}

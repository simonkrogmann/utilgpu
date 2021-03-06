#pragma once

#include <chrono>

#include <glbinding/gl/gl.h>
#include <utilgpu/cpp/FileWatcher.h>
#include <utilgpu/gl/FrameTimeDisplay.h>

using namespace gl;

namespace util
{
namespace viewport
{
struct Viewport;
}
class Framebuffer;

class Renderer
{
public:
    Renderer();
    virtual ~Renderer();

    virtual void init() = 0;
    virtual void reload() = 0;
    void render(const util::viewport::Viewport& viewport);

    void renderOffscreen(const Framebuffer* fbo,
                         const util::viewport::Viewport& resolution);
    void renderToFile(const util::viewport::Viewport& resolution);
    void toggleFrameTimeDisplay();
    virtual void saveFramebuffers();
    virtual void keyPressed(int key, bool controlPressed);

protected:
    void addDependentPath(const util::File& path);
    void addDependentPath(const std::string& path);
    virtual void draw(const util::viewport::Viewport& viewport) = 0;

private:
    std::unique_ptr<Framebuffer> m_fileFBO;
    util::FileWatcher m_fileWatcher;

    bool m_measureFrameTime = false;
    util::FrameTimeDisplay m_frameTimeDisplay;
};
}  // namespace util

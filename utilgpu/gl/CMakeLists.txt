find_package(glbinding REQUIRED)

set(target gl)

set(sources
    base.cpp
    viewport.cpp
    Program.cpp
    Shader.cpp
    Texture.cpp
    Framebuffer.cpp
    Drawable.cpp
    ScreenAlignedQuad.cpp
    FrameTimeDisplay.cpp
    Renderer.cpp
    GroundPlane.cpp
)

set(includes
    base.h
    viewport.h
    Program.h
    Shader.h
    Texture.h
    Framebuffer.h
    Drawable.h
    ScreenAlignedQuad.h
    FrameTimeDisplay.h
    Renderer.h
    GroundPlane.h
)

set(resources
    shader/screenalignedquad.vert
    shader/onscreendisplay.frag
    shader/groundplane.vert
)

set(libraries
    cpp
    qt
    glbinding::glbinding
)

create_library(${project} ${target} "${sources}" "${includes}" "${libraries}")
generate_resource_header(${project} ${target} "${resources}")

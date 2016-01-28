find_package(glbinding REQUIRED)

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
)

set(resources
    shader/screenalignedquad.vert
    shader/onscreendisplay.frag
)

set(libraries
    cpp
    qt
    glbinding::glbinding
)

create_library(gl "${sources}" "${includes}" "${libraries}")
generate_resource_header(gl "${resources}")

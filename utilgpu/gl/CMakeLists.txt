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
)

set(libraries
    cpp
    qt
    glbinding::glbinding
)

create_target(gl "${sources}" "${includes}" "${libraries}")

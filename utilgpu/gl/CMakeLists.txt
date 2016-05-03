find_package(glbinding REQUIRED)
find_package(glm REQUIRED)
find_package(Qt5OpenGL REQUIRED)

set(target gl)

set(sources
    base.cpp
    viewport.cpp
    image.cpp
    Program.cpp
    Shader.cpp
    Texture.cpp
    Framebuffer.cpp
    Drawable.cpp
    ScreenAlignedQuad.cpp
    FrameTimeDisplay.cpp
    Renderer.cpp
    GroundPlane.cpp
    ShadowMap.cpp
)

set(includes
    base.h
    viewport.h
    image.h
    Program.h
    Shader.h
    Texture.h
    Framebuffer.h
    Drawable.h
    ScreenAlignedQuad.h
    FrameTimeDisplay.h
    Renderer.h
    GroundPlane.h
    ShadowMap.h
    Model.h
)

set(resources
    shader/screenalignedquad.vert
    shader/onscreendisplay.frag
    shader/groundplane.vert
    shader/shadowmap.vert
    shader/shadowmap.frag
    shader/shadowmap_lookup.frag
)

set(libraries
    cpp
    glbinding::glbinding
    Qt5::OpenGL
)

create_library(${project} ${target} "${sources}" "${includes}" "${libraries}")
generate_resource_header(${project} ${target} "${resources}")

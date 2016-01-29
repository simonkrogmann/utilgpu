set(sources
    resource_loader.cpp
)

set(includes

)

set(libraries
    cpp
)

create_executable(${project} utilgpu-resource-loader "${sources}" "${includes}" "${libraries}")

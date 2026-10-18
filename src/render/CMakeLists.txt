add_library(multisplit-render STATIC
    crop-math.cpp
    crop-renderer.cpp
    transform.cpp
)
target_link_libraries(multisplit-render PUBLIC OBS::libobs)

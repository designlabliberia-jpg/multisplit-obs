add_library(multisplit-presets STATIC preset-manager.cpp)
target_link_libraries(multisplit-presets PUBLIC OBS::libobs)

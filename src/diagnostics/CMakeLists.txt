add_library(multisplit-diagnostics STATIC performance-monitor.cpp)
target_link_libraries(multisplit-diagnostics PUBLIC OBS::libobs)

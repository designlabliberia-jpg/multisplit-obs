#include "source-manager.hpp"

SourceManager::~SourceManager() {
    release_source();
}

void SourceManager::set_source(const char* source_name) {
    release_source();
    if (source_name && *source_name) {
        base_source = obs_get_source_by_name(source_name);
    }
}

void SourceManager::release_source() {
    if (base_source) {
        obs_source_release(base_source);
        base_source = nullptr;
    }
}

#pragma once
extern "C" {
#include <obs-source.h>
}
#include <string>

class SourceManager {
    obs_source_t* base_source = nullptr;

public:
    SourceManager() = default;
    ~SourceManager();

    void set_source(const char* source_name);
    obs_source_t* get_source() { return base_source; }

private:
    void release_source();
};

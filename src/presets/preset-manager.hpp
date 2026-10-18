#pragma once
#include <string>
#include <vector>

struct Preset {
    std::string name;
    float center_x;
    float center_y;
    float zoom;
    float rotation;
    bool flip_h;
    bool flip_v;
};

class PresetManager {
public:
    static std::string Serialize(const Preset& preset);
    static Preset Deserialize(const std::string& json);
};

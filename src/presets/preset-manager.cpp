#include "preset-manager.hpp"
#include <sstream>
#include <iomanip>

std::string PresetManager::Serialize(const Preset &p)
{
	std::stringstream ss;
	ss << "{\"name\":\"" << p.name << "\","
	   << "\"x\":" << p.center_x << ","
	   << "\"y\":" << p.center_y << ","
	   << "\"z\":" << p.zoom << ","
	   << "\"r\":" << p.rotation << ","
	   << "\"fh\":" << (p.flip_h ? 1 : 0) << ","
	   << "\"fv\":" << (p.flip_v ? 1 : 0) << "}";
	return ss.str();
}

Preset PresetManager::Deserialize(const std::string &json)
{
	Preset p;
	p.name = "Custom";
	p.center_x = 0.5f;
	p.center_y = 0.5f;
	p.zoom = 1.0f;
	p.rotation = 0.0f;
	p.flip_h = false;
	p.flip_v = false;

	// Simple robust parsing helpers
	auto extract_string = [](const std::string &str, const std::string &key) -> std::string {
		size_t pos = str.find("\"" + key + "\":\"");
		if (pos == std::string::npos)
			return "";
		pos += key.length() + 4;
		size_t end = str.find("\"", pos);
		if (end == std::string::npos)
			return "";
		return str.substr(pos, end - pos);
	};

	auto extract_float = [](const std::string &str, const std::string &key) -> float {
		size_t pos = str.find("\"" + key + "\":");
		if (pos == std::string::npos)
			return 0.0f;
		pos += key.length() + 3;
		return std::stof(str.substr(pos));
	};

	std::string name = extract_string(json, "name");
	if (!name.empty())
		p.name = name;

	// Direct float extraction
	size_t px = json.find("\"x\":");
	if (px != std::string::npos)
		p.center_x = std::stof(json.substr(px + 4));

	size_t py = json.find("\"y\":");
	if (py != std::string::npos)
		p.center_y = std::stof(json.substr(py + 4));

	size_t pz = json.find("\"z\":");
	if (pz != std::string::npos)
		p.zoom = std::stof(json.substr(pz + 4));

	size_t pr = json.find("\"r\":");
	if (pr != std::string::npos)
		p.rotation = std::stof(json.substr(pr + 4));

	size_t pfh = json.find("\"fh\":");
	if (pfh != std::string::npos)
		p.flip_h = (std::stoi(json.substr(pfh + 5)) != 0);

	size_t pfv = json.find("\"fv\":");
	if (pfv != std::string::npos)
		p.flip_v = (std::stoi(json.substr(pfv + 5)) != 0);

	return p;
}

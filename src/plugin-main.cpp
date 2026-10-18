extern "C" {
#include <obs-module.h>
}

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE("multisplit", "en-US")

extern struct obs_source_info multisplit_source_info;

bool obs_module_load(void)
{
	obs_register_source(&multisplit_source_info);
	return true;
}

void obs_module_unload(void)
{
	// Cleanup
}

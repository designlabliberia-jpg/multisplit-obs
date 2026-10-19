#include "obs-compat.hpp"

OBS_DECLARE_MODULE()
{
	return "multisplit";
}

OBS_MODULE_USE_DEFAULT_LOCALE("multisplit", "en-US")

extern struct obs_source_info multisplit_source_info;

#ifdef __cplusplus
extern "C" {
#endif

OBS_EXPORT uint32_t obs_module_ver(void)
{
	return LIBOBS_API_VER;
}

OBS_EXPORT bool obs_module_load(void)
{
	obs_register_source(&multisplit_source_info);
	return true;
}

OBS_EXPORT void obs_module_unload(void)
{
	// Cleanup
}

#ifdef __cplusplus
}
#endif

#pragma once

#if defined(CORE_EXPORTS)
#define EXPORT_SPEC __declspec(dllexport)
#else
#define EXPORT_SPEC __declspec(dllimport)
#endif // defined(CORE_EXPORTS)

typedef unsigned int(__stdcall* WebUIInterfaceFunc)(const wchar_t*, wchar_t*, int);

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus
	EXPORT_SPEC int WebUI1_Initialize(void* parentWindowHandle);
	EXPORT_SPEC int WebUI1_Finalize(void* parentWindowHandle);
	EXPORT_SPEC int WebUI1_Resize(void* parentWindowHandle, int width, int height);
	EXPORT_SPEC int WebUI1_Navigate(void* parentWindowHandle, const wchar_t* url);
	EXPORT_SPEC int WebUI1_SetInterface(void* parentWindowHandle, const wchar_t* name, WebUIInterfaceFunc callback);
	EXPORT_SPEC int WebUI1_SendEvent(void* parentWindowHandle, const wchar_t* name, const wchar_t* content);
#ifdef __cplusplus
}
#endif // __cplusplus

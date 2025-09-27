#include "Wrap_Platform.h"
#include <iostream>

bool PlatformWrapper::LoadDLL(const char* dllName) 
{
    hDll = LoadLibraryA(dllName);
    if (!hDll) 
    {
        std::cerr << "[PlatformWrapper] Failed to load DLL: " << dllName << "\n";
        return false;
    }

    // Load all function pointers from DLL
    fnCreate      = (tCreatePlatform)GetProcAddress(hDll, "CreatePlatform");
    fnDestroy     = (tDestroyPlatform)GetProcAddress(hDll, "DestroyPlatform");
    fnInit        = (tInitPlatform)GetProcAddress(hDll, "InitPlatform");
    fnShow        = (tShowPlatform)GetProcAddress(hDll, "ShowPlatform");
    fnHide        = (tHidePlatform)GetProcAddress(hDll, "HidePlatform");
    fnShutdown    = (tShutdownPlatform)GetProcAddress(hDll, "ShutdownPlatform");
    fnGetHandle   = (tGetPlatformHandle)GetProcAddress(hDll, "GetPlatformHandle");
    fnSetTitle    = (tSetPlatformTitle)GetProcAddress(hDll, "SetPlatformTitle");
    fnGetTitle    = (tGetPlatformTitle)GetProcAddress(hDll, "GetPlatformTitle");
    fnSetSize     = (tSetPlatformSize)GetProcAddress(hDll, "SetPlatformSize");
    fnSetPosition = (tSetPlatformPosition)GetProcAddress(hDll, "SetPlatformPosition");
    fnSetTimer    = (tSetPlatformTimer)GetProcAddress(hDll, "SetPlatformTimer");
    fnKillTimer   = (tKillPlatformTimer)GetProcAddress(hDll, "KillPlatformTimer");

    if (!fnCreate || !fnDestroy || !fnInit || !fnShow || !fnHide || !fnShutdown || !fnGetHandle) 
    {
        std::cerr << "[PlatformWrapper] Failed to load essential DLL functions\n";
        return false;
    }

    // Create platform instance
    platformInstance = fnCreate();
    std::cout << "[PlatformWrapper] Platform instance created successfully\n";
    return true;
}

/// <summary>Initializes the platform instance</summary>
/// <param name="bus">Optional EventBus pointer</param>
void PlatformWrapper::Initialize(void* bus) 
{ 
    if (fnInit) fnInit(platformInstance, bus); 
}

/// <summary>Shows the platform window</summary>
void PlatformWrapper::ShowWindow() 
{ 
    if (fnShow) fnShow(platformInstance); 
}

/// <summary>Hides the platform window</summary>
void PlatformWrapper::HideWindow() 
{ 
    if (fnHide) fnHide(platformInstance); 
}

/// <summary>Shuts down the platform instance</summary>
void PlatformWrapper::ShutdownPlatform() 
{ 
    if (fnShutdown) fnShutdown(platformInstance); 
}

/// <summary>Returns the HWND handle of the platform window</summary>
HWND PlatformWrapper::GetHWND() 
{ 
    return fnGetHandle ? (HWND)fnGetHandle(platformInstance) : nullptr; 
}

/// <summary>Sets the window title</summary>
void PlatformWrapper::SetWindowTitle(const std::string& title) 
{ 
    if (fnSetTitle) fnSetTitle(platformInstance, (char*)title.c_str()); 
}

/// <summary>Gets the window title</summary>
std::string PlatformWrapper::GetWindowTitle() 
{ 
    return fnGetTitle ? std::string(fnGetTitle(platformInstance)) : ""; 
}

/// <summary>Sets the window size</summary>
void PlatformWrapper::SetWindowSize(float w, float h) 
{ 
    if (fnSetSize) fnSetSize(platformInstance, w, h); 
}

/// <summary>Sets the window position</summary>
void PlatformWrapper::SetWindowPosition(float x, float y) 
{ 
    if (fnSetPosition) fnSetPosition(platformInstance, x, y); 
}

/// <summary>Sets a platform timer</summary>
void PlatformWrapper::SetTimer(uint32_t id, uint32_t intervalMs) 
{ 
    if (fnSetTimer) fnSetTimer(platformInstance, id, intervalMs); 
}

/// <summary>Kills a platform timer</summary>
void PlatformWrapper::KillTimer(uint32_t id) 
{ 
    if (fnKillTimer) fnKillTimer(platformInstance, id); 
}

/// <summary>Destructor. Releases all resources and unloads the DLL</summary>
PlatformWrapper::~PlatformWrapper() 
{
    if (platformInstance && fnDestroy) 
    {
        fnDestroy(platformInstance);
        std::cout << "[PlatformWrapper] Platform instance destroyed\n";
    }
    if (hDll) 
    {
        FreeLibrary(hDll);
        std::cout << "[PlatformWrapper] DLL unloaded\n";
    }
}

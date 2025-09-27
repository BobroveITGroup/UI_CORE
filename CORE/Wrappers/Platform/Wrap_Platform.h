#pragma once
#include <Windows.h>
#include <string>
#include <cstdint>

typedef void* (*tCreatePlatform)();
typedef void  (*tDestroyPlatform)(void*);
typedef void  (*tInitPlatform)(void*, void*);
typedef void  (*tShowPlatform)(void*);
typedef void  (*tHidePlatform)(void*);
typedef void  (*tShutdownPlatform)(void*);
typedef void* (*tGetPlatformHandle)(void*);
typedef void  (*tSetPlatformTitle)(void*, char*);
typedef char* (*tGetPlatformTitle)(void*);
typedef void  (*tSetPlatformSize)(void*, float, float);
typedef void  (*tSetPlatformPosition)(void*, float, float);
typedef void  (*tSetPlatformTimer)(void*, uint32_t, uint32_t);
typedef void  (*tKillPlatformTimer)(void*, uint32_t);

/// <summary>
/// Wrapper for a platform DLL (window creation, timers, and other OS interactions)
/// </summary>
class PlatformWrapper 
{
private:
    HMODULE hDll = nullptr;            ///< Handle to the loaded DLL
    void* platformInstance = nullptr;  ///< Pointer to the platform instance

    // Function pointers loaded from DLL
    tCreatePlatform      fnCreate = nullptr;
    tDestroyPlatform     fnDestroy = nullptr;
    tInitPlatform        fnInit = nullptr;
    tShowPlatform        fnShow = nullptr;
    tHidePlatform        fnHide = nullptr;
    tShutdownPlatform    fnShutdown = nullptr;
    tGetPlatformHandle   fnGetHandle = nullptr;
    tSetPlatformTitle    fnSetTitle = nullptr;
    tGetPlatformTitle    fnGetTitle = nullptr;
    tSetPlatformSize     fnSetSize = nullptr;
    tSetPlatformPosition fnSetPosition = nullptr;
    tSetPlatformTimer    fnSetTimer = nullptr;
    tKillPlatformTimer   fnKillTimer = nullptr;

public:
    /// <summary>
    /// Loads the DLL and resolves all platform functions
    /// </summary>
    /// <param name="dllName">DLL filename</param>
    /// <returns>True if DLL loaded successfully, false otherwise</returns>
    bool LoadDLL(const char* dllName);

    /// <summary>
    /// Initializes the platform instance
    /// </summary>
    /// <param name="bus">Optional pointer to EventBus, can be nullptr</param>
    void Initialize(void* bus = nullptr);

    /// <summary>Shows the platform window</summary>
    void ShowWindow();

    /// <summary>Hides the platform window</summary>
    void HideWindow();

    /// <summary>Shuts down the platform instance and releases resources</summary>
    void ShutdownPlatform();

    /// <summary>Returns the HWND handle of the platform window</summary>
    /// <returns>Window handle</returns>
    HWND GetHWND();

    /// <summary>Sets the window title</summary>
    /// <param name="title">New window title</param>
    void SetWindowTitle(const std::string& title);

    /// <summary>Gets the window title</summary>
    /// <returns>Current window title</returns>
    std::string GetWindowTitle();

    /// <summary>Sets the window size</summary>
    /// <param name="w">Width in pixels</param>
    /// <param name="h">Height in pixels</param>
    void SetWindowSize(float w, float h);

    /// <summary>Sets the window position</summary>
    /// <param name="x">X coordinate</param>
    /// <param name="y">Y coordinate</param>
    void SetWindowPosition(float x, float y);

    /// <summary>Sets a platform timer</summary>
    /// <param name="id">Timer identifier</param>
    /// <param name="intervalMs">Interval in milliseconds</param>
    void SetTimer(uint32_t id, uint32_t intervalMs);

    /// <summary>Kills a platform timer</summary>
    /// <param name="id">Timer identifier</param>
    void KillTimer(uint32_t id);

    /// <summary>
    /// Destructor. Releases all platform resources and unloads the DLL
    /// </summary>
    ~PlatformWrapper();
};

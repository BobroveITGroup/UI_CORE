#pragma once
#include <Windows.h>
#include <string>
#include "IPlugin_UI.h"
#include "Wrap_Renderer.h"

/// <summary>
/// Universal wrapper for any UI plugin implementing IPlugin_UI
/// Provides a clean interface to interact with UI plugins loaded from DLLs
/// without dealing directly with DLL function pointers.
/// </summary>
class UI_Wrapper {
    HMODULE hDll = nullptr;                    // Handle to the loaded DLL
    UI_CORE::IPlugin_UI* instance = nullptr;  // Pointer to the UI plugin instance

    // Function pointers for the generic UI plugin
    using tCreate = UI_CORE::IPlugin_UI* (*)();
    using tDestroy = void (*)(UI_CORE::IPlugin_UI*);
    using tSetSize = void (*)(UI_CORE::IPlugin_UI*, float, float);
    using tSetPosition = void (*)(UI_CORE::IPlugin_UI*, float, float);
    using tSetVisible = void (*)(UI_CORE::IPlugin_UI*, bool);
    using tGetVisible = bool (*)(UI_CORE::IPlugin_UI*);
    using tRender = void (*)(UI_CORE::IPlugin_UI*);
    using tInit = void (*)(UI_CORE::IPlugin_UI*, UI_CORE::EventBus*, RendererWrapper*);

    tCreate fnCreate = nullptr;
    tDestroy fnDestroy = nullptr;
    tSetSize fnSetSize = nullptr;
    tSetPosition fnSetPosition = nullptr;
    tSetVisible fnSetVisible = nullptr;
    tGetVisible fnGetVisible = nullptr;
    tRender fnRender = nullptr;
    tInit fnInit = nullptr;

public:
    /// <summary>Load the DLL and retrieve all function pointers</summary>
    /// <param name="dllName">Path to the DLL file</param>
    /// <param name="createFnName">Name of the creation function in the DLL</param>
    /// <param name="destroyFnName">Name of the destruction function in the DLL</param>
    /// <returns>True if the DLL loaded successfully and the instance was created</returns>
    bool LoadDLL(const char* dllName, const char* createFnName, const char* destroyFnName) {
        hDll = LoadLibraryA(dllName);
        if (!hDll) return false;

        fnCreate  = (tCreate)GetProcAddress(hDll, createFnName);
        fnDestroy = (tDestroy)GetProcAddress(hDll, destroyFnName);

        // Optional functions
        fnSetSize     = (tSetSize)GetProcAddress(hDll, "UI_SetSize");
        fnSetPosition = (tSetPosition)GetProcAddress(hDll, "UI_SetPosition");
        fnSetVisible  = (tSetVisible)GetProcAddress(hDll, "UI_SetVisible");
        fnGetVisible  = (tGetVisible)GetProcAddress(hDll, "UI_GetVisible");
        fnRender      = (tRender)GetProcAddress(hDll, "UI_Render");
        fnInit        = (tInit)GetProcAddress(hDll, "UI_Init");

        if (!fnCreate || !fnDestroy) return false;

        instance = fnCreate();
        return instance != nullptr;
    }

    /// <summary>Initialize the UI plugin with the event bus and renderer</summary>
    void Init(UI_CORE::EventBus* bus, RendererWrapper* renderer) {
        if (fnInit && instance) fnInit(instance, bus, renderer);
    }

    /// <summary>Set the size of the UI element</summary>
    void SetSize(float w, float h) {
        if (fnSetSize) fnSetSize(instance, w, h);
    }

    /// <summary>Set the position of the UI element</summary>
    void SetPosition(float x, float y) {
        if (fnSetPosition) fnSetPosition(instance, x, y);
    }

    /// <summary>Set the visibility of the UI element</summary>
    void SetVisible(bool visible) {
        if (fnSetVisible) fnSetVisible(instance, visible);
    }

    /// <summary>Get the current visibility state</summary>
    bool GetVisible() {
        return fnGetVisible ? fnGetVisible(instance) : false;
    }

    /// <summary>Render the UI element</summary>
    void Render() {
        if (fnRender) fnRender(instance);
    }

    /// <summary>Release resources and unload the DLL</summary>
    ~UI_Wrapper() {
        if (hDll && instance && fnDestroy) {
            fnDestroy(instance);
            instance = nullptr;
        }

        if (hDll) {
            FreeLibrary(hDll);
            hDll = nullptr;
        }

        fnCreate = nullptr;
        fnDestroy = nullptr;
        fnSetSize = nullptr;
        fnSetPosition = nullptr;
        fnSetVisible = nullptr;
        fnGetVisible = nullptr;
        fnRender = nullptr;
        fnInit = nullptr;
    }
};

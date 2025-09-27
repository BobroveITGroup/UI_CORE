#include "ColorBox.h"
#include "IPlugin_UI.h"

using namespace UI_CORE;

extern "C" {

    // ==============================
    // Initialize UI_ColorBox instance
    // ==============================
    __declspec(dllexport) void UI_ColorBox_Init(IPlugin_UI* ptr, EventBus* bus, RendererWrapper* renderer)
    {
        if (ptr)
            ptr->Init(bus, renderer);
    }

    // ==============================
    // Create a new UI_ColorBox instance
    // ==============================
    __declspec(dllexport) IPlugin_UI* CreateUI_ColorBox()
    {
        return new UI_ColorBox();
    }

    // ==============================
    // Destroy a UI_ColorBox instance
    // ==============================
    __declspec(dllexport) void DestroyUI_ColorBox(IPlugin_UI* ptr)
    {
        if (ptr)
            delete ptr;
    }

    // ==============================
    // Set the size of the UI_ColorBox
    // ==============================
    __declspec(dllexport) void UI_ColorBox_SetSize(IPlugin_UI* ptr, float w, float h)
    {
        if (ptr) ptr->SetSize(w, h);
    }

    // ==============================
    // Set the position of the UI_ColorBox
    // ==============================
    __declspec(dllexport) void UI_ColorBox_SetPosition(IPlugin_UI* ptr, float x, float y)
    {
        if (ptr) ptr->SetPosition(x, y);
    }

    // ==============================
    // Set visibility of the UI_ColorBox
    // ==============================
    __declspec(dllexport) void UI_ColorBox_SetVisible(IPlugin_UI* ptr, bool v)
    {
        if (ptr) ptr->SetVisible(v);
    }

    // ==============================
    // Get visibility status of the UI_ColorBox
    // ==============================
    __declspec(dllexport) bool UI_ColorBox_GetVisible(IPlugin_UI* ptr)
    {
        return ptr ? ptr->GetVisible() : false;
    }

    // ==============================
    // Render the UI_ColorBox (draw to renderer)
    // ==============================
    __declspec(dllexport) void UI_ColorBox_Render(IPlugin_UI* ptr)
    {
        if (ptr)
            static_cast<UI_ColorBox*>(ptr)->Render();
    }
}

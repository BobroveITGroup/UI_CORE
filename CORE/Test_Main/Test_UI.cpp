#include "Wrap_Platform.h"
#include "Wrap_Renderer.h"
#include "Wrap_UI.h"
#include "EventBus.h"

#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    setlocale(LC_ALL, "RUS"); // Optional: for Russian console output

    // ===== EventBus =====
    // Central event handler for UI and other plugins
    UI_CORE::EventBus EventLoop;

    // ===== Platform (Window / OS Abstraction) =====
    PlatformWrapper platform;
    if (!platform.LoadDLL("Platform_Windows.dll")) {
        std::cerr << "[Error] Failed to load Platform DLL\n";
        return -1;
    }
    platform.Initialize(&EventLoop);
    platform.SetWindowTitle("Plugin System Demo");
    platform.ShowWindow();

    HWND hwnd = platform.GetHWND();
    if (!hwnd) {
        std::cerr << "[Error] Invalid HWND\n";
        return -1;
    }

    // ===== Renderer (Direct2D / OpenGL / Vulkan) =====
    RendererWrapper renderer;
    if (!renderer.LoadDLL("Renderer_D2D1.dll")) {
        std::cerr << "[Error] Failed to load Renderer DLL\n";
        return -1;
    }
    renderer.Initialize(hwnd);

    // ===== UI Plugins (IPlugin_UI instances) =====
    UI_Wrapper box1, box2, box3;

    // Load the same UI DLL multiple times for separate instances
    if (!box1.LoadDLL("UI_ColorBox.dll") ||
        !box2.LoadDLL("UI_ColorBox.dll") ||
        !box3.LoadDLL("UI_ColorBox.dll")) {
        std::cerr << "[Error] Failed to load UI_ColorBox DLL\n";
        return -1;
    }

    // Initialize UI plugins with EventBus and Renderer
    box1.Init(&EventLoop, &renderer);
    box2.Init(&EventLoop, &renderer);
    box3.Init(&EventLoop, &renderer);

    // Set positions, sizes, and visibility
    box1.SetPosition(50,  50);  box1.SetSize(120, 80);  box1.SetVisible(true);
    box2.SetPosition(200, 100); box2.SetSize(100, 120); box2.SetVisible(true);
    box3.SetPosition(350, 150); box3.SetSize(150, 90);  box3.SetVisible(true);

    // ===== Main loop =====
    MSG msg{};
    while (true)
    {
        // Process Windows messages
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT) return 0;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // Process plugin events
        EventLoop.ProcessEvents();

        // Render frame
        renderer.Begin();
        renderer.Clear();

        // Render UI plugin instances
        box1.Render();
        box2.Render();
        box3.Render();

        renderer.End();

        // Limit to ~60 FPS
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    return 0;
}

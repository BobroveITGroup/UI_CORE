#pragma once

#include "IPlugin_Platform.h"
#include <functional>
#include <Windows.h>

constexpr size_t MAX_CHILDREN = 32;

namespace UI_CORE {

    /**
     * @brief Structure for mapping Win32 messages to custom event callbacks.
     * Example: hash("WM_KEYDOWN") → callback function.
     */
    struct Win32MessageHandler
    {
        uint64_t hash; ///< Hash of the event type (e.g., "WM_KEYDOWN")
        std::function<void(HWND, WPARAM, LPARAM, EventBus* eventBus)> callback;
    };

    /**
     * @class Platform_Win32
     * @brief Plugin implementation of a Win32-based windowing system.
     *
     * Responsibilities:
     * - Creates and manages a native Win32 window
     * - Dispatches system messages via EventBus
     * - Provides APIs for size, position, icons, timers
     * - Hosts child UI plugins inside the window
     */
    class Platform_Win32 : public IPlugin_Platform
    {
    public:
        Platform_Win32();
        ~Platform_Win32();

        // ===== IPlugin Metadata =====
        const char* GetName() override    { return "Win32Platform"; }
        const char* GetAuthor() override  { return "Mikhail"; }
        const char* GetVersion() override { return "0.1"; }
        PluginType GetPluginType() override { return PluginType::Platform; }

        // ===== IPlugin Lifecycle =====
        void InitializePlugin(EventBus* bus) override;
        void ShutdownPlugin() override;

        // ===== Window Management =====
        char* GetTitle() override;
        void SetTitle(char* title) override;

        windowSize GetSize() override;
        void SetSize(float width, float height) override;

        windowPosition GetPosition() override;
        void SetPosition(float x, float y) override;

        void SetIconFromFile(const char* filepath) override;
        void SetIconFromMemory(const iconData& img) override;

        void Show() override;
        void Hide() override;

        void* GetNativeHandle() override;

        // ===== Timers =====
        void SetTimer(uint32_t id, uint32_t intervalMs) override;
        void KillTimer(uint32_t id) override;

        // ===== Event Handling =====
        void WindowProcedure(const void* data, size_t size, uint64_t typeId) override;

        void AddHandler(uint64_t typeHash, std::function<void(HWND, WPARAM, LPARAM, EventBus* bus)> cb);
        void RemoveHandler(uint64_t typeHash);

        // ===== Child UI Plugins =====
        void AddChild(IPlugin_UI* child);
        void RemoveChild(IPlugin_UI* child);

        size_t GetChildCount();
        IPlugin_UI* GetChild(size_t index);

        // ===== Diagnostics =====
        uint64_t GetMemoryUsage();  
        double GetCPUUsage();            
        double GetUptime();              

        void OnEvent(const Event& e) { /* TODO: forward to bus or children */ }

    private:
        // ===== Internal State =====
        HWND hwnd;
        HINSTANCE hInstance;
        char title[256];
        EventBus* eventBus;

        // ===== Message Handling =====
        static LRESULT CALLBACK StaticWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
        LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

        static constexpr size_t MAX_HANDLERS = 128;
        Win32MessageHandler handlers[MAX_HANDLERS];
        size_t handlerCount = 0;

        // ===== Child Plugins =====
        IPlugin_UI* children[MAX_CHILDREN];
        size_t childCount = 0;
    };

} // namespace UI_CORE

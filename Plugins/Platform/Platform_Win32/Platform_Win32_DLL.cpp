#include "Platform_Win32.h"

using namespace UI_CORE;

#ifdef __cplusplus
extern "C" {
#endif

    // ===== Создание / уничтожение =====
    __declspec(dllexport) Platform_Win32* CreatePlatform() {
        return new Platform_Win32();
    }

    __declspec(dllexport) void DestroyPlatform(Platform_Win32* platform) {
        if (platform) delete platform;
    }

    // ===== Инициализация / завершение =====
    __declspec(dllexport) void InitPlatform(Platform_Win32* platform, EventBus* bus) {
        if (platform) platform->InitializePlugin(bus);
    }

    __declspec(dllexport) void ShutdownPlatform(Platform_Win32* platform) {
        if (platform) platform->ShutdownPlugin();
    }

    // ===== Управление окном =====
    __declspec(dllexport) void ShowPlatform(Platform_Win32* platform) {
        if (platform) platform->Show();
    }

    __declspec(dllexport) void HidePlatform(Platform_Win32* platform) {
        if (platform) platform->Hide();
    }

    __declspec(dllexport) void SetPlatformTitle(Platform_Win32* platform, char* title) {
        if (platform) platform->SetTitle(title);
    }

    __declspec(dllexport) char* GetPlatformTitle(Platform_Win32* platform) {
        return (platform) ? platform->GetTitle() : nullptr;
    }

    __declspec(dllexport) void SetPlatformSize(Platform_Win32* platform, float width, float height) {
        if (platform) platform->SetSize(width, height);
    }

    __declspec(dllexport) windowSize GetPlatformSize(Platform_Win32* platform) {
        return (platform) ? platform->GetSize() : windowSize{ 0, 0 };
    }

    __declspec(dllexport) void SetPlatformPosition(Platform_Win32* platform, float x, float y) {
        if (platform) platform->SetPosition(x, y);
    }

    __declspec(dllexport) windowPosition GetPlatformPosition(Platform_Win32* platform) {
        return (platform) ? platform->GetPosition() : windowPosition{ 0, 0 };
    }

    __declspec(dllexport) void* GetPlatformHandle(Platform_Win32* platform) {
        return (platform) ? platform->GetNativeHandle() : nullptr;
    }

    // ===== Таймеры =====
    __declspec(dllexport) void SetPlatformTimer(Platform_Win32* platform, uint32_t id, uint32_t intervalMs) {
        if (platform) platform->SetTimer(id, intervalMs);
    }

    __declspec(dllexport) void KillPlatformTimer(Platform_Win32* platform, uint32_t id) {
        if (platform) platform->KillTimer(id);
    }

    // ===== Метаданные плагина =====
    __declspec(dllexport) const char* GetPlatformName(Platform_Win32* platform) {
        return (platform) ? platform->GetName() : "";
    }

    __declspec(dllexport) const char* GetPlatformAuthor(Platform_Win32* platform) {
        return (platform) ? platform->GetAuthor() : "";
    }

    __declspec(dllexport) const char* GetPlatformVersion(Platform_Win32* platform) {
        return (platform) ? platform->GetVersion() : "";
    }

    __declspec(dllexport) PluginType GetPlatformType(Platform_Win32* platform) {
        return (platform) ? platform->GetPluginType() : PluginType::Unknown;
    }

    // ===== Мониторинг =====
    __declspec(dllexport) uint64_t GetPlatformMemoryUsage(Platform_Win32* platform) {
        return (platform) ? platform->GetMemoryUsage() : 0;
    }

    __declspec(dllexport) double GetPlatformCPUUsage(Platform_Win32* platform) {
        return (platform) ? platform->GetCPUUsage() : 0.0;
    }

    __declspec(dllexport) double GetPlatformUptime(Platform_Win32* platform) {
        return (platform) ? platform->GetUptime() : 0.0;
    }

#ifdef __cplusplus
}
#endif

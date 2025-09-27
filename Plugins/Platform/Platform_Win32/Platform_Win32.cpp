#include "Platform_Win32.h"
#include <cstring>
#include <psapi.h>
#include "Handlers.h"

namespace UI_CORE {

    // =====================================================
    // Constructor / Destructor
    // =====================================================

    Platform_Win32::Platform_Win32()
        : hwnd(nullptr), hInstance(GetModuleHandle(nullptr)), eventBus(nullptr)
    {
        std::memset(title, 0, sizeof(title));
    }

    Platform_Win32::~Platform_Win32()
    {
        if (hwnd)
            DestroyWindow(hwnd);
    }

    // =====================================================
    // Plugin Lifecycle
    // =====================================================

    void Platform_Win32::InitializePlugin(EventBus* bus)
    {
        eventBus = bus;

        // Register window class
        WNDCLASSW wc{};
        wc.lpfnWndProc   = Platform_Win32::StaticWndProc;
        wc.hInstance     = hInstance;
        wc.lpszClassName = L"UI_CORE_Win32Window";
        wc.hCursor       = LoadCursor(nullptr, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

        RegisterClassW(&wc);

        wchar_t wtitle[256] = {};
        MultiByteToWideChar(CP_UTF8, 0, title, -1, wtitle, 256);

        // Create main application window
        hwnd = CreateWindowExW(
            0,
            wc.lpszClassName,
            wtitle,
            WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
            nullptr, nullptr, hInstance, this
        );

        // Register default event handlers
        AddHandler(WM_CLOSE,      [this](HWND hwnd, WPARAM w, LPARAM l, EventBus* bus) { Handlers::OnClose(hwnd, w, l, this->eventBus); });
        AddHandler(WM_SIZE,       [this](HWND hwnd, WPARAM w, LPARAM l, EventBus* bus) { Handlers::OnResize(hwnd, w, l, this->eventBus); });
        AddHandler(WM_SETFOCUS,   [this](HWND hwnd, WPARAM w, LPARAM l, EventBus* bus) { Handlers::OnFocus(hwnd, w, l, this->eventBus); });
        AddHandler(WM_SYSCOMMAND, [this](HWND hwnd, WPARAM w, LPARAM l, EventBus* bus) {
            if ((w & 0xFFF0) == SC_MINIMIZE) Handlers::OnMinimize(hwnd, w, l, this->eventBus);
            else if ((w & 0xFFF0) == SC_MAXIMIZE) Handlers::OnMaximize(hwnd, w, l, this->eventBus);
        });

        // Keyboard events
        AddHandler(WM_KEYDOWN, [this](HWND hwnd, WPARAM w, LPARAM l, EventBus* bus) { Handlers::OnKeyDown(hwnd, w, l, this->eventBus); });
        AddHandler(WM_KEYUP,   [this](HWND hwnd, WPARAM w, LPARAM l, EventBus* bus) { Handlers::OnKeyUp(hwnd, w, l, this->eventBus); });
        AddHandler(WM_CHAR,    [this](HWND hwnd, WPARAM w, LPARAM l, EventBus* bus) { Handlers::OnChar(hwnd, w, l, this->eventBus); });

        // Mouse events
        AddHandler(WM_MOUSEMOVE,   [this](HWND hwnd, WPARAM w, LPARAM l, EventBus* bus) { Handlers::OnMouseMove(hwnd, w, l, this->eventBus); });
        AddHandler(WM_LBUTTONDOWN, [this](HWND hwnd, WPARAM w, LPARAM l, EventBus* bus) { Handlers::OnLButtonDown(hwnd, w, l, this->eventBus); });
        AddHandler(WM_LBUTTONUP,   [this](HWND hwnd, WPARAM w, LPARAM l, EventBus* bus) { Handlers::OnLButtonUp(hwnd, w, l, this->eventBus); });
        AddHandler(WM_RBUTTONDOWN, [this](HWND hwnd, WPARAM w, LPARAM l, EventBus* bus) { Handlers::OnRButtonDown(hwnd, w, l, this->eventBus); });
        AddHandler(WM_RBUTTONUP,   [this](HWND hwnd, WPARAM w, LPARAM l, EventBus* bus) { Handlers::OnRButtonUp(hwnd, w, l, this->eventBus); });
        AddHandler(WM_MOUSEWHEEL,  [this](HWND hwnd, WPARAM w, LPARAM l, EventBus* bus) { Handlers::OnMouseWheel(hwnd, w, l, this->eventBus); });

        // Timers and device notifications
        AddHandler(WM_TIMER,        [this](HWND hwnd, WPARAM w, LPARAM l, EventBus* bus) { Handlers::OnTimer(hwnd, w, l, this->eventBus); });
        AddHandler(WM_DEVICECHANGE, [this](HWND hwnd, WPARAM w, LPARAM l, EventBus* bus) { Handlers::OnDeviceChange(hwnd, w, l, this->eventBus); });

        // Internal frame timer (16 ms ≈ 60 FPS)
        SetTimer(1, 16);
    }

    void Platform_Win32::ShutdownPlugin()
    {
        if (hwnd)
        {
            DestroyWindow(hwnd);
            hwnd = nullptr;
        }
    }

    // =====================================================
    // Window Properties
    // =====================================================

    char* Platform_Win32::GetTitle() { return title; }

    void Platform_Win32::SetTitle(char* newTitle)
    {
        strncpy_s(title, sizeof(title), newTitle, _TRUNCATE);
        if (hwnd)
            SetWindowTextA(hwnd, title);
    }

    windowSize Platform_Win32::GetSize()
    {
        RECT r{};
        windowSize s{};
        if (hwnd && GetWindowRect(hwnd, &r))
        {
            s.width  = float(r.right - r.left);
            s.height = float(r.bottom - r.top);
            s.x = float(r.left);
            s.y = float(r.top);
        }
        return s;
    }

    void Platform_Win32::SetSize(float width, float height)
    {
        if (hwnd)
            SetWindowPos(hwnd, nullptr, 0, 0, int(width), int(height), SWP_NOMOVE | SWP_NOZORDER);
    }

    windowPosition Platform_Win32::GetPosition()
    {
        RECT r{};
        windowPosition pos{};
        if (hwnd && GetWindowRect(hwnd, &r))
        {
            pos.x = float(r.left);
            pos.y = float(r.top);
        }
        return pos;
    }

    void Platform_Win32::SetPosition(float x, float y)
    {
        if (hwnd)
            SetWindowPos(hwnd, nullptr, int(x), int(y), 0, 0, SWP_NOSIZE | SWP_NOZORDER);
    }

    void Platform_Win32::SetIconFromFile(const char* filepath)
    {
        HICON hIcon = (HICON)LoadImageA(nullptr, filepath, IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE);
        if (hIcon && hwnd)
            SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
    }

    void Platform_Win32::SetIconFromMemory(const iconData& img)
    {
        // TODO: implement RGBA → HICON conversion
    }

    void Platform_Win32::Show()  { if (hwnd) ShowWindow(hwnd, SW_SHOW); }
    void Platform_Win32::Hide()  { if (hwnd) ShowWindow(hwnd, SW_HIDE); }
    void* Platform_Win32::GetNativeHandle() { return hwnd; }

    // =====================================================
    // Timers
    // =====================================================

    void Platform_Win32::SetTimer(uint32_t id, uint32_t intervalMs)
    {
        if (hwnd)
            ::SetTimer(hwnd, id, intervalMs, nullptr);
    }

    void Platform_Win32::KillTimer(uint32_t id)
    {
        if (hwnd)
            ::KillTimer(hwnd, id);
    }

    // =====================================================
    // Window Procedure
    // =====================================================

    void Platform_Win32::WindowProcedure(const void* data, size_t size, uint64_t typeId)
    {
        // Custom event packets can be decoded here if needed
    }

    LRESULT CALLBACK Platform_Win32::StaticWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        Platform_Win32* self = nullptr;
        if (msg == WM_NCCREATE)
        {
            CREATESTRUCT* cs = (CREATESTRUCT*)lParam;
            self = (Platform_Win32*)cs->lpCreateParams;
            SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)self);
        }
        else
            self = (Platform_Win32*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

        return (self ? self->WndProc(hwnd, msg, wParam, lParam) : DefWindowProc(hwnd, msg, wParam, lParam));
    }

    LRESULT CALLBACK Platform_Win32::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        uint64_t msgHash = static_cast<uint64_t>(msg);

        for (size_t i = 0; i < handlerCount; ++i)
        {
            if (handlers[i].hash == msgHash)
                handlers[i].callback(hwnd, wParam, lParam, eventBus);
        }

        return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    // =====================================================
    // Handlers Management
    // =====================================================

    void Platform_Win32::AddHandler(uint64_t typeHash, std::function<void(HWND, WPARAM, LPARAM, EventBus*)> cb)
    {
        if (handlerCount < MAX_HANDLERS)
            handlers[handlerCount++] = { typeHash, cb };
    }

    void Platform_Win32::RemoveHandler(uint64_t typeHash)
    {
        for (size_t i = 0; i < handlerCount; ++i)
        {
            if (handlers[i].hash == typeHash)
            {
                handlers[i] = handlers[--handlerCount];
                break;
            }
        }
    }

    // =====================================================
    // Child UI Plugins
    // =====================================================

    void Platform_Win32::AddChild(IPlugin_UI* child)
    {
        if (childCount < MAX_CHILDREN)
            children[childCount++] = child;
    }

    void Platform_Win32::RemoveChild(IPlugin_UI* child)
    {
        for (size_t i = 0; i < childCount; ++i)
        {
            if (children[i] == child)
            {
                children[i] = children[--childCount];
                children[childCount] = nullptr;
                break;
            }
        }
    }

    size_t Platform_Win32::GetChildCount() { return childCount; }

    IPlugin_UI* Platform_Win32::GetChild(size_t index)
    {
        return (index < childCount ? children[index] : nullptr);
    }

    // =====================================================
    // Diagnostics
    // =====================================================

    uint64_t Platform_Win32::GetMemoryUsage()
    {
        PROCESS_MEMORY_COUNTERS_EX pmc;
        if (GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc)))
            return static_cast<uint64_t>(pmc.WorkingSetSize); // physical memory in bytes
        return 0;
    }

    double Platform_Win32::GetCPUUsage()
    {
        static ULARGE_INTEGER lastSysKernel, lastSysUser;
        static ULARGE_INTEGER lastProcKernel, lastProcUser;
        static bool firstRun = true;

        FILETIME ftSysIdle, ftSysKernel, ftSysUser;
        FILETIME ftProcCreation, ftProcExit, ftProcKernel, ftProcUser;

        if (!GetSystemTimes(&ftSysIdle, &ftSysKernel, &ftSysUser) ||
            !GetProcessTimes(GetCurrentProcess(), &ftProcCreation, &ftProcExit, &ftProcKernel, &ftProcUser))
            return -1.0;

        ULARGE_INTEGER sysKernel, sysUser, procKernel, procUser;
        sysKernel.LowPart  = ftSysKernel.dwLowDateTime;
        sysKernel.HighPart = ftSysKernel.dwHighDateTime;
        sysUser.LowPart    = ftSysUser.dwLowDateTime;
        sysUser.HighPart   = ftSysUser.dwHighDateTime;
        procKernel.LowPart = ftProcKernel.dwLowDateTime;
        procKernel.HighPart= ftProcKernel.dwHighDateTime;
        procUser.LowPart   = ftProcUser.dwLowDateTime;
        procUser.HighPart  = ftProcUser.dwHighDateTime;

        if (firstRun) {
            lastSysKernel = sysKernel;
            lastSysUser   = sysUser;
            lastProcKernel= procKernel;
            lastProcUser  = procUser;
            firstRun = false;
            return 0.0;
        }

        ULONGLONG sysKernelDiff = sysKernel.QuadPart - lastSysKernel.QuadPart;
        ULONGLONG sysUserDiff   = sysUser.QuadPart - lastSysUser.QuadPart;
        ULONGLONG procKernelDiff= procKernel.QuadPart - lastProcKernel.QuadPart;
        ULONGLONG procUserDiff  = procUser.QuadPart - lastProcUser.QuadPart;

        lastSysKernel = sysKernel;
        lastSysUser   = sysUser;
        lastProcKernel= procKernel;
        lastProcUser  = procUser;

        ULONGLONG sysTotal  = sysKernelDiff + sysUserDiff;
        ULONGLONG procTotal = procKernelDiff + procUserDiff;

        if (sysTotal == 0) return 0.0;

        return (100.0 * (double)procTotal / (double)sysTotal); // % CPU usage
    }

    double Platform_Win32::GetUptime()
    {
        return static_cast<double>(GetTickCount64()) / 1000.0; // uptime in seconds
    }

} // namespace UI_CORE

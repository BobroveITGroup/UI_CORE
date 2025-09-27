#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include "EventBus.h"

#include <Windows.h>
#include <cstdint>
#include <functional>

namespace UI_CORE {

    using Win32Handler = std::function<void(HWND, WPARAM, LPARAM, EventBus* bus)>;

    struct HandlerEntry
    {
        uint64_t msgHash;
        Win32Handler callback;
    };

    namespace Handlers {

        // ===== Window =====
        void OnClose(HWND hwnd, WPARAM, LPARAM,EventBus*);
        void OnResize(HWND hwnd, WPARAM, LPARAM,EventBus*);
        void OnFocus(HWND hwnd, WPARAM, LPARAM,EventBus*);
        void OnMinimize(HWND hwnd, WPARAM, LPARAM,EventBus*);
        void OnMaximize(HWND hwnd, WPARAM, LPARAM,EventBus*);

        // ===== Keyboard =====
        void OnKeyDown(HWND hwnd, WPARAM, LPARAM,EventBus*);
        void OnKeyUp(HWND hwnd, WPARAM, LPARAM,EventBus*);
        void OnChar(HWND hwnd, WPARAM, LPARAM,EventBus*);

        // ===== Mouse =====
        void OnMouseMove(HWND hwnd, WPARAM, LPARAM,EventBus*);
        void OnLButtonDown(HWND hwnd, WPARAM, LPARAM,EventBus*);
        void OnLButtonUp(HWND hwnd, WPARAM, LPARAM,EventBus*);
        void OnRButtonDown(HWND hwnd, WPARAM, LPARAM,EventBus*);
        void OnRButtonUp(HWND hwnd, WPARAM, LPARAM,EventBus*);
        void OnMouseWheel(HWND hwnd, WPARAM, LPARAM,EventBus*);

        // ===== System =====
        void OnTimer(HWND hwnd, WPARAM, LPARAM,EventBus*);
        void OnDeviceChange(HWND hwnd, WPARAM, LPARAM,EventBus*);

    } // namespace Handlers
} // namespace UI_CORE

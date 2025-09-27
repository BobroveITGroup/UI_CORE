#include "Handlers.h"
#include <iostream>
#include "EventBus.h"

namespace UI_CORE {
    namespace Handlers {

        // ===== Window =====
        void OnClose(HWND hwnd, WPARAM, LPARAM, EventBus* eventBus)
        {
            if (eventBus)
            {
                Event e{};
                std::strncpy(e.type, "Close", sizeof(e.type) - 1);
                eventBus->Publish(e);
            }
        }

        void OnResize(HWND hwnd, WPARAM, LPARAM lParam, EventBus* eventBus)
        {
            int width = LOWORD(lParam);
            int height = HIWORD(lParam);

            if (eventBus)
            {
                Event e{};
                std::strncpy(e.type, "Resize", sizeof(e.type) - 1);
                e.data[0] = static_cast<uint8_t>(width & 0xFF);
                e.data[1] = static_cast<uint8_t>((width >> 8) & 0xFF);
                e.data[2] = static_cast<uint8_t>(height & 0xFF);
                e.data[3] = static_cast<uint8_t>((height >> 8) & 0xFF);
                e.dataSize = 4;
                eventBus->Publish(e);
            }
            else
            {
                std::cout << "[Handler] Window Resize: event bus is NULL!!!!!!" << "\n";
            }
        }

        void OnFocus(HWND hwnd, WPARAM, LPARAM, EventBus* eventBus)
        {
            if (eventBus)
            {
                Event e{};
                std::strncpy(e.type, "Focus", sizeof(e.type) - 1);
                eventBus->Publish(e);
            }
        }

        void OnMinimize(HWND hwnd, WPARAM, LPARAM, EventBus* eventBus)
        {
            if (eventBus)
            {
                Event e{};
                std::strncpy(e.type, "Minimize", sizeof(e.type) - 1);
                eventBus->Publish(e);
            }
        }

        void OnMaximize(HWND hwnd, WPARAM, LPARAM, EventBus* eventBus)
        {
            if (eventBus)
            {
                Event e{};
                std::strncpy(e.type, "Maximize", sizeof(e.type) - 1);
                eventBus->Publish(e);
            }
        }

        // ===== Keyboard =====
        void OnKeyDown(HWND hwnd, WPARAM wParam, LPARAM, EventBus* eventBus)
        {
            if (eventBus)
            {
                Event e{};
                std::strncpy(e.type, "KeyDown", sizeof(e.type) - 1);
                e.data[0] = static_cast<uint8_t>(wParam & 0xFF);
                e.dataSize = 1;
                eventBus->Publish(e);
            }
        }

        void OnKeyUp(HWND hwnd, WPARAM wParam, LPARAM, EventBus* eventBus)
        {
            if (eventBus)
            {
                Event e{};
                std::strncpy(e.type, "KeyUp", sizeof(e.type) - 1);
                e.data[0] = static_cast<uint8_t>(wParam & 0xFF);
                e.dataSize = 1;
                eventBus->Publish(e);
            }
        }

        void OnChar(HWND hwnd, WPARAM wParam, LPARAM, EventBus* eventBus)
        {
            if (eventBus)
            {
                Event e{};
                std::strncpy(e.type, "CharInput", sizeof(e.type) - 1);
                e.data[0] = static_cast<uint8_t>(wParam & 0xFF);
                e.dataSize = 1;
                eventBus->Publish(e);
            }
        }

        // ===== Mouse =====
        void OnMouseMove(HWND hwnd, WPARAM, LPARAM lParam, EventBus* eventBus)
        {
            int x = LOWORD(lParam);
            int y = HIWORD(lParam);
            if (eventBus)
            {
                Event e{};
                std::strncpy(e.type, "MouseMove", sizeof(e.type) - 1);
                e.data[0] = static_cast<uint8_t>(x & 0xFF);
                e.data[1] = static_cast<uint8_t>(y & 0xFF);
                e.dataSize = 2;
                eventBus->Publish(e);
            }
        }

        void OnLButtonDown(HWND hwnd, WPARAM, LPARAM lParam, EventBus* eventBus)
        {
            if (eventBus)
            {
                Event e{};
                std::strncpy(e.type, "LButtonDown", sizeof(e.type) - 1);
                e.data[0] = static_cast<uint8_t>(LOWORD(lParam) & 0xFF);
                e.data[1] = static_cast<uint8_t>(HIWORD(lParam) & 0xFF);
                e.dataSize = 2;
                eventBus->Publish(e);
            }
        }

        void OnLButtonUp(HWND hwnd, WPARAM, LPARAM lParam, EventBus* eventBus)
        {
            if (eventBus)
            {
                Event e{};
                std::strncpy(e.type, "LButtonUp", sizeof(e.type) - 1);
                e.data[0] = static_cast<uint8_t>(LOWORD(lParam) & 0xFF);
                e.data[1] = static_cast<uint8_t>(HIWORD(lParam) & 0xFF);
                e.dataSize = 2;
                eventBus->Publish(e);
            }
        }

        void OnRButtonDown(HWND hwnd, WPARAM, LPARAM lParam, EventBus* eventBus)
        {
            if (eventBus)
            {
                Event e{};
                std::strncpy(e.type, "RButtonDown", sizeof(e.type) - 1);
                e.data[0] = static_cast<uint8_t>(LOWORD(lParam) & 0xFF);
                e.data[1] = static_cast<uint8_t>(HIWORD(lParam) & 0xFF);
                e.dataSize = 2;
                eventBus->Publish(e);
            }
        }

        void OnRButtonUp(HWND hwnd, WPARAM, LPARAM lParam, EventBus* eventBus)
        {
            if (eventBus)
            {
                Event e{};
                std::strncpy(e.type, "RButtonUp", sizeof(e.type) - 1);
                e.data[0] = static_cast<uint8_t>(LOWORD(lParam) & 0xFF);
                e.data[1] = static_cast<uint8_t>(HIWORD(lParam) & 0xFF);
                e.dataSize = 2;
                eventBus->Publish(e);
            }
        }

        void OnMouseWheel(HWND hwnd, WPARAM wParam, LPARAM, EventBus* eventBus)
        {
            int delta = GET_WHEEL_DELTA_WPARAM(wParam);
            if (eventBus)
            {
                Event e{};
                std::strncpy(e.type, "MouseWheel", sizeof(e.type) - 1);
                e.data[0] = static_cast<uint8_t>(delta & 0xFF);
                e.data[1] = static_cast<uint8_t>((delta >> 8) & 0xFF);
                e.dataSize = 2;
                eventBus->Publish(e);
            }
        }

        // ===== System =====
        void OnTimer(HWND hwnd, WPARAM wParam, LPARAM, EventBus* eventBus)
        {
            if (eventBus)
            {
                Event e{};
                std::strncpy(e.type, "Timer", sizeof(e.type) - 1);
                e.data[0] = static_cast<uint8_t>(wParam & 0xFF);
                e.dataSize = 1;
                eventBus->Publish(e);
            }
            InvalidateRect(hwnd, NULL, FALSE);
        }

        void OnDeviceChange(HWND hwnd, WPARAM wParam, LPARAM, EventBus* eventBus)
        {
            if (eventBus)
            {
                Event e{};
                std::strncpy(e.type, "DeviceChange", sizeof(e.type) - 1);
                e.data[0] = static_cast<uint8_t>(wParam & 0xFF);
                e.dataSize = 1;
                eventBus->Publish(e);
            }
        }

    } // namespace Handlers
} // namespace UI_CORE

#pragma once

#include "IPlugin.h"
#include "IPlugin_UI.h"

namespace UI_CORE
{
    /// <summary>
    /// Represents the size of a window.
    /// </summary>
    struct WindowSize
    {
        float x;
        float y;
        float width;
        float height;
    };

    /// <summary>
    /// Represents the position of a window.
    /// </summary>
    struct WindowPosition
    {
        float x;
        float y;
    };

    /// <summary>
    /// Represents an icon image in memory.
    /// </summary>
    struct IconData
    {
        const void* pixels; ///< Pointer to the pixel data (RGBA)
        size_t width;       ///< Width of the image in pixels
        size_t height;      ///< Height of the image in pixels
        size_t stride;      ///< Number of bytes per row
    };

    /// <summary>
    /// Platform plugin interface — a bridge between the OS and the EventBus.
    /// </summary>
    struct IPlugin_Platform : IPlugin
    {
        // =======================
        // ===== Window Title ====
        // =======================

        /// <summary>Gets the window title.</summary>
        /// <returns>Pointer to a null-terminated string.</returns>
        virtual char* GetTitle() = 0;

        /// <summary>Sets the window title.</summary>
        /// <param name="title">Null-terminated string to set as the title.</param>
        virtual void SetTitle(char* title) = 0;

        // =======================
        // ===== Window Size =====
        // =======================

        /// <summary>Gets the current size of the window.</summary>
        /// <returns>A <see cref="WindowSize"/> structure with window dimensions and position.</returns>
        virtual WindowSize GetSize() = 0;

        /// <summary>Sets the window size.</summary>
        /// <param name="width">Width of the window in pixels.</param>
        /// <param name="height">Height of the window in pixels.</param>
        virtual void SetSize(float width, float height) = 0;

        // =======================
        // ===== Window Position =
        // =======================

        /// <summary>Gets the current position of the window.</summary>
        /// <returns>A <see cref="WindowPosition"/> structure with X and Y coordinates.</returns>
        virtual WindowPosition GetPosition() = 0;

        /// <summary>Sets the window position.</summary>
        /// <param name="x">X coordinate of the window.</param>
        /// <param name="y">Y coordinate of the window.</param>
        virtual void SetPosition(float x, float y) = 0;

        // =======================
        // ===== Window Icon =====
        // =======================

        /// <summary>Sets the window icon from a file (PNG, ICO, etc.).</summary>
        /// <param name="filepath">Path to the image file.</param>
        virtual void SetIconFromFile(const char* filepath) = 0;

        /// <summary>Sets the window icon from an already loaded memory buffer.</summary>
        /// <param name="img">Icon data in memory.</param>
        virtual void SetIconFromMemory(const IconData& img) = 0;

        // =======================
        // ===== Visibility ======
        // =======================

        /// <summary>Shows the window.</summary>
        virtual void Show() = 0;

        /// <summary>Hides the window.</summary>
        virtual void Hide() = 0;

        // =======================
        // ===== Native Handle ===
        // =======================

        /// <summary>Gets the native OS handle of the window.</summary>
        /// <returns>Pointer to the native window handle.</returns>
        virtual void* GetNativeHandle() = 0;

        // =======================
        // ===== Timers ==========
        // =======================

        /// <summary>Sets a timer.</summary>
        /// <param name="id">Timer identifier.</param>
        /// <param name="intervalMs">Interval in milliseconds.</param>
        virtual void SetTimer(uint32_t id, uint32_t intervalMs) = 0;

        /// <summary>Kills a previously set timer.</summary>
        /// <param name="id">Timer identifier.</param>
        virtual void KillTimer(uint32_t id) = 0;

        // =======================
        // ===== Window Events ===
        // =======================

        /// <summary>Handles OS-specific window events.</summary>
        /// <param name="data">Pointer to event data.</param>
        /// <param name="size">Size of the data buffer.</param>
        /// <param name="typeId">Identifier of the event type.</param>
        virtual void WindowProcedure(const void* data, size_t size, uint64_t typeId) = 0;

        // =======================
        // ===== System Info =====
        // =======================

        /// <summary>Gets the current memory usage of the process in bytes.</summary>
        virtual uint64_t GetMemoryUsage() = 0;

        /// <summary>Gets the current CPU usage percentage of the process.</summary>
        virtual double GetCPUUsage() = 0;

        /// <summary>Gets the uptime of the process in seconds.</summary>
        virtual double GetUptime() = 0;

        // =======================
        // ===== UI Children =====
        // =======================

        /// <summary>Adds a child UI element.</summary>
        /// <param name="child">Pointer to the child plugin UI.</param>
        virtual void AddChild(IPlugin_UI* child) = 0;

        /// <summary>Removes a child UI element.</summary>
        /// <param name="child">Pointer to the child plugin UI.</param>
        virtual void RemoveChild(IPlugin_UI* child) = 0;
    };
}

#pragma once

#include "IPlugin.h"

namespace UI_CORE
{
    /// <summary>
    /// Represents a color with RGBA channels.
    /// </summary>
    struct Color
    {
        float r;
        float g;
        float b;
        float a;
    };

    /// <summary>
    /// Abstract handle for a texture or image.
    /// </summary>
    struct ImageHandle {};

    /// <summary>
    /// Represents a linear gradient for rectangles.
    /// </summary>
    struct Gradient
    {
        Color start; ///< Gradient start color
        Color end;   ///< Gradient end color
        float x_1;   ///< Start X coordinate
        float y_1;   ///< Start Y coordinate
        float x_2;   ///< End X coordinate
        float y_2;   ///< End Y coordinate
    };

    /// <summary>
    /// Interface for a renderer plugin with support for window/device context.
    /// </summary>
    struct IPlugin_Renderer : public IPlugin
    {
        // =======================
        // ===== Lifecycle =======
        // =======================

        /// <summary>Initializes the renderer with a window or device context.</summary>
        /// <param name="windowHandle">Pointer to the window handle (HWND or equivalent).</param>
        virtual void InitializeRenderer(void* windowHandle) = 0;

        /// <summary>Shuts down the renderer and releases all resources.</summary>
        virtual void ShutdownRenderer() = 0;

        /// <summary>Clears the current frame before drawing.</summary>
        virtual void ClearFrame() = 0;

        /// <summary>Renders all accumulated commands/objects.</summary>
        virtual void RenderFrame() = 0;

        /// <summary>Sets the viewport size.</summary>
        /// <param name="width">Width in pixels.</param>
        /// <param name="height">Height in pixels.</param>
        virtual void SetViewportSize(float width, float height) = 0;

        /// <summary>Submits a command or object for rendering.</summary>
        /// <param name="command">Pointer to the command or object.</param>
        virtual void SubmitRenderCommand(void* command) = 0;

        /// <summary>Updates the renderer state (e.g., swap chain, resizing).</summary>
        virtual void Update() = 0;

        // =======================
        // ===== Basic Primitives
        // =======================

        /// <summary>Draws a line.</summary>
        virtual void DrawLine(float x1, float y1, float x2, float y2, Color color, float thickness = 1.0f) = 0;

        /// <summary>Draws a rectangle.</summary>
        virtual void DrawRectangle(float x, float y, float width, float height, Color color, float thickness = 0.0f) = 0;

        /// <summary>Draws a circle.</summary>
        virtual void DrawCircle(float cx, float cy, float radius, Color color, float thickness = 0.0f) = 0;

        /// <summary>Draws text.</summary>
        virtual void DrawText_u(const char* text, float x, float y, Color color, float fontSize = 16.0f) = 0;

        /// <summary>Draws a rounded rectangle.</summary>
        virtual void DrawRoundedRectangle(float x, float y, float width, float height, float radius, Color color, float thickness = 0.0f) = 0;

        // =======================
        // ===== Advanced Primitives
        // =======================

        /// <summary>Draws a polygon with an arbitrary number of points.</summary>
        virtual void DrawPolygon(const float* points, size_t pointCount, Color color, float thickness = 0.0f) = 0;

        /// <summary>Draws an image or texture.</summary>
        virtual void DrawImage(ImageHandle* image, float x, float y, float width, float height, float alpha = 1.0f) = 0;

        /// <summary>Draws a rectangle with a gradient.</summary>
        virtual void DrawGradientRect(float x, float y, float width, float height, Gradient gradient) = 0;

        /// <summary>Draws a shadow or glow effect.</summary>
        virtual void DrawShadow(float x, float y, float width, float height, Color color, float blurRadius) = 0;

        /// <summary>Draws a cubic Bezier curve with four control points.</summary>
        virtual void DrawBezier(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3, Color color, float thickness = 1.0f) = 0;

        // =======================
        // ===== Transform & Clip
        // =======================

        /// <summary>Sets the clipping rectangle.</summary>
        virtual void SetClippingRect(float x, float y, float width, float height) = 0;

        /// <summary>Clears the clipping rectangle.</summary>
        virtual void ClearClipping() = 0;

        /// <summary>Applies a transformation to subsequent primitives.</summary>
        virtual void SetTransform(float translateX, float translateY, float scaleX, float scaleY, float rotationDeg) = 0;

        /// <summary>Resets the transformation.</summary>
        virtual void ResetTransform() = 0;

        /// <summary>Sets the blending mode / alpha blending.</summary>
        virtual void SetBlendMode(int mode) = 0;

        /// <summary>Sets horizontal text alignment (0=left, 1=center, 2=right).</summary>
        virtual void SetTextAlignment(int alignment) = 0;

        /// <summary>Enables or disables text wrapping.</summary>
        virtual void SetTextWrapping(bool wrap) = 0;

        // =======================
        // ===== Frame Control ===
        // =======================

        /// <summary>Begins a new frame. Called before all draw commands.</summary>
        virtual void BeginDraw() = 0;

        /// <summary>Ends the frame and finalizes rendering.</summary>
        virtual void EndDraw() = 0;
    };
}

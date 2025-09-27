#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include "IPlugin_Renderer.h"

#include <Windows.h>
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>
#include <string>

#pragma comment(lib,"d2d1")
#pragma comment(lib,"dwrite")
#pragma comment(lib,"windowscodecs")

namespace UI_CORE
{
    typedef IPlugin_Renderer* RendererHandle;

    /// <summary>
    /// Direct2D/DirectWrite based rendering plugin implementation.
    /// Provides hardware-accelerated 2D drawing for Windows platform.
    /// </summary>
    class Renderer_D2D1 : IPlugin_Renderer
    {
    public:
        /// <summary>Initialize the renderer with a given window handle.</summary>
        virtual void InitializeRenderer(void* windowHandle) override;

        /// <summary>Release all renderer resources and shut down.</summary>
        virtual void ShutdownRenderer() override;

        /// <summary>Clear the frame before drawing.</summary>
        virtual void ClearFrame() override;

        /// <summary>Render all submitted draw commands to the screen.</summary>
        virtual void RenderFrame() override;

        /// <summary>Set the viewport dimensions for rendering.</summary>
        virtual void SetViewportSize(float width, float height) override;

        /// <summary>Submit a generic render command to the pipeline.</summary>
        virtual void SubmitRenderCommand(void* command) override;

        /// <summary>Update renderer state (animations, resources, etc.).</summary>
        virtual void Update() override;

        /// <summary>Draw a line segment between two points.</summary>
        virtual void DrawLine(float x1, float y1, float x2, float y2, Color color, float thickness) override;

        /// <summary>Draw a rectangle outline or filled shape.</summary>
        virtual void DrawRectangle(float x, float y, float width, float height, Color color, float thickness) override;

        /// <summary>Draw a circle at given coordinates.</summary>
        virtual void DrawCircle(float cx, float cy, float radius, Color color, float thickness) override;

        /// <summary>Draw UTF-8 encoded text at given coordinates.</summary>
        virtual void DrawText_u(const char* text, float x, float y, Color color, float fontSize) override;

        /// <summary>Draw a rounded rectangle shape.</summary>
        virtual void DrawRoundedRectangle(float x, float y, float width, float height, float radius, Color color, float thickness) override;

        /// <summary>Draw a polygon from an array of points.</summary>
        virtual void DrawPolygon(const float* points, size_t pointCount, Color color, float thickness) override;

        /// <summary>Draw an image at given position and size.</summary>
        virtual void DrawImage(ImageHandle* image, float x, float y, float width, float height, float alpha) override;

        /// <summary>Draw a rectangle filled with a gradient.</summary>
        virtual void DrawGradientRect(float x, float y, float width, float height, Gradient gradient) override;

        /// <summary>Draw a blurred shadow behind a rectangle.</summary>
        virtual void DrawShadow(float x, float y, float width, float height, Color color, float blurRadius) override;

        /// <summary>Draw a cubic Bezier curve.</summary>
        virtual void DrawBezier(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3, Color color, float thickness) override;

        /// <summary>Restrict rendering to a clipping rectangle.</summary>
        virtual void SetClippingRect(float x, float y, float width, float height) override;

        /// <summary>Clear any active clipping region.</summary>
        virtual void ClearClipping() override;

        /// <summary>Apply translation, scaling, and rotation transform.</summary>
        virtual void SetTransform(float translateX, float translateY, float scaleX, float scaleY, float rotationDeg) override;

        /// <summary>Reset all transformations to identity.</summary>
        virtual void ResetTransform() override;

        /// <summary>Set blending mode for draw operations.</summary>
        virtual void SetBlendMode(int mode) override;

        /// <summary>Set alignment mode for text rendering.</summary>
        virtual void SetTextAlignment(int alignment) override;

        /// <summary>Enable or disable text word wrapping.</summary>
        virtual void SetTextWrapping(bool wrap) override;

        /// <summary>Begin a new drawing batch.</summary>
        virtual void BeginDraw() override;

        /// <summary>End the drawing batch and flush to GPU.</summary>
        virtual void EndDraw() override;

        /// <summary>Get the renderer plugin name.</summary>
        virtual const char* GetName() { return "Renderer_D2D1"; };

        /// <summary>Get the renderer plugin author name.</summary>
        virtual const char* GetAuthor() { return "Michael Bobrove"; };

        /// <summary>Get the renderer plugin version.</summary>
        virtual const char* GetVersion() { return "0.0.1"; };

        /// <summary>Get the plugin type (Renderer).</summary>
        virtual PluginType GetPluginType() { return PluginType::Renderer; };

        /// <summary>Shutdown the plugin and release resources.</summary>
        virtual void ShutdownPlugin();

        /// <summary>Handle an incoming framework event.</summary>
        virtual void OnEvent(const Event& e);

    private:
        HWND hwnd;
        PAINTSTRUCT ps;

        ID2D1Factory* m_pFactory_d2d1;
        IDWriteFactory* m_pFactory_dwrite;
        IWICImagingFactory* m_pFactory_iwic;
        ID2D1HwndRenderTarget* m_pRenderTarget;
    };
}

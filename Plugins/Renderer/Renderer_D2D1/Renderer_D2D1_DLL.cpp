// RendererDLL.cpp
#include "Renderer_D2D1.h"

using namespace UI_CORE;

#ifdef __cplusplus
extern "C" {
#endif

    // ===== Создание / уничтожение =====
    __declspec(dllexport) Renderer_D2D1* CreateRenderer() {
        return new Renderer_D2D1();
    }

    __declspec(dllexport) void DestroyRenderer(Renderer_D2D1* renderer) {
        if (renderer) delete renderer;
    }

    // ===== Инициализация =====
    __declspec(dllexport) void InitRenderer(Renderer_D2D1* renderer, void* hwnd) {
        if (renderer) renderer->InitializeRenderer(hwnd);
    }

    __declspec(dllexport) void ShutdownRenderer(Renderer_D2D1* renderer) {
        if (renderer) renderer->ShutdownRenderer();
    }

    __declspec(dllexport) void SetViewportSize(Renderer_D2D1* renderer, float width, float height) {
        if (renderer) renderer->SetViewportSize(width, height);
    }

    // ===== Цикл кадра =====
    __declspec(dllexport) void BeginDraw(Renderer_D2D1* renderer) {
        if (renderer) renderer->BeginDraw();
    }

    __declspec(dllexport) void EndDraw(Renderer_D2D1* renderer) {
        if (renderer) renderer->EndDraw();
    }

    __declspec(dllexport) void ClearFrame(Renderer_D2D1* renderer) {
        if (renderer) renderer->ClearFrame();
    }

    __declspec(dllexport) void RenderFrame(Renderer_D2D1* renderer) {
        if (renderer) renderer->RenderFrame();
    }

    // ===== Примитивы =====
    __declspec(dllexport) void DrawLine(Renderer_D2D1* renderer,
        float x1, float y1, float x2, float y2,
        float r, float g, float b, float a,
        float thickness) {
        if (renderer) renderer->DrawLine(x1, y1, x2, y2, { r, g, b, a }, thickness);
    }

    __declspec(dllexport) void DrawPolygon(Renderer_D2D1* renderer,
        const float* points,
        size_t pointCount,
        float r, float g, float b, float a,
        float thickness)
    {
        if (renderer)
            renderer->DrawPolygon(points, pointCount, { r, g, b, a }, thickness);
    }

    __declspec(dllexport) void DrawRectangle(Renderer_D2D1* renderer,
        float x, float y, float width, float height,
        float r, float g, float b, float a,
        float thickness) {
        if (renderer) renderer->DrawRectangle(x, y, width, height, { r, g, b, a }, thickness);
    }

    __declspec(dllexport) void DrawCircle(Renderer_D2D1* renderer,
        float cx, float cy, float radius,
        float r, float g, float b, float a,
        float thickness) {
        if (renderer) renderer->DrawCircle(cx, cy, radius, { r, g, b, a }, thickness);
    }

    __declspec(dllexport) void DrawText_u(Renderer_D2D1* renderer,
        const char* text,
        float x, float y,
        float r, float g, float b, float a,
        float fontSize) {
        if (renderer) renderer->DrawText_u(text, x, y, { r, g, b, a }, fontSize);
    }

#ifdef __cplusplus
}
#endif

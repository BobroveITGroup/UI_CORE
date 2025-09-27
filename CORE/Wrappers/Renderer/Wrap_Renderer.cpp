#include "Wrap_Renderer.h"
#include <iostream>

bool RendererWrapper::LoadDLL(const char* dllName) {
    hDll = LoadLibraryA(dllName);
    if (!hDll) return false;

    // Load function pointers from DLL
    fnCreate          = (tCreateRenderer)GetProcAddress(hDll, "CreateRenderer");
    fnDestroy         = (tDestroyRenderer)GetProcAddress(hDll, "DestroyRenderer");
    fnInit            = (tInitRenderer)GetProcAddress(hDll, "InitRenderer");
    fnBegin           = (tBeginDraw)GetProcAddress(hDll, "BeginDraw");
    fnEnd             = (tEndDraw)GetProcAddress(hDll, "EndDraw");
    fnClear           = (tClearFrame)GetProcAddress(hDll, "ClearFrame");
    fnLine            = (tDrawLine)GetProcAddress(hDll, "DrawLine");
    fnRect            = (tDrawRectangle)GetProcAddress(hDll, "DrawRectangle");
    fnCircle          = (tDrawCircle)GetProcAddress(hDll, "DrawCircle");
    fnText            = (tDrawText_u)GetProcAddress(hDll, "DrawText_u");
    fnPolygon         = (tDrawPolygon)GetProcAddress(hDll, "DrawPolygon");
    fnSetViewportSize = (tSetViewportSize)GetProcAddress(hDll, "SetViewportSize");

    // Minimal required functions
    if (!fnCreate || !fnDestroy || !fnInit || !fnBegin || !fnEnd || !fnClear || !fnLine || !fnRect) {
        std::cerr << "[RendererWrapper] Failed to load essential functions!\n";
        return false;
    }

    // Optional: warning if some non-essential functions are missing
    if (!fnSetViewportSize || !fnCircle || !fnText || !fnPolygon) {
        std::cerr << "[RendererWrapper] Warning: Some optional functions not loaded.\n";
    }

    // Create renderer instance
    renderer = fnCreate();
    return true;
}

void RendererWrapper::Initialize(HWND hwnd) {
    if (fnInit) fnInit(renderer, hwnd);
}

void RendererWrapper::Begin() {
    if (fnBegin) fnBegin(renderer);
}

void RendererWrapper::End() {
    if (fnEnd) fnEnd(renderer);
}

void RendererWrapper::Clear() {
    if (fnClear) fnClear(renderer);
}

void RendererWrapper::DrawLine(float x1, float y1, float x2, float y2,
                               float r, float g, float b, float a, float thickness) {
    if (fnLine) fnLine(renderer, x1, y1, x2, y2, r, g, b, a, thickness);
}

void RendererWrapper::DrawRect(float x, float y, float w, float h,
                               float r, float g, float b, float a, float thickness) {
    if (fnRect) fnRect(renderer, x, y, w, h, r, g, b, a, thickness);
}

void RendererWrapper::DrawCircle(float cx, float cy, float radius,
                                 float r, float g, float b, float a, float thickness) {
    if (fnCircle) fnCircle(renderer, cx, cy, radius, r, g, b, a, thickness);
}

void RendererWrapper::DrawText(const std::string& text, float x, float y,
                               float r, float g, float b, float a, float fontSize) {
    if (fnText) fnText(renderer, text.c_str(), x, y, r, g, b, a, fontSize);
}

void RendererWrapper::DrawPolygon(const float* points, size_t pointCount,
                                  float r, float g, float b, float a, float thickness) {
    if (!renderer || !fnPolygon || !points || pointCount < 2) return;
    fnPolygon(renderer, points, pointCount, r, g, b, a, thickness);
}

void RendererWrapper::SetViewportSize(float width, float height) {
    if (fnSetViewportSize) {
        fnSetViewportSize(renderer, width, height);
        std::cout << "[RendererWrapper] Viewport size set: " << width << "x" << height << "\n";
    }
}

RendererWrapper::~RendererWrapper() {
    if (renderer && fnDestroy) fnDestroy(renderer);
    if (hDll) FreeLibrary(hDll);
}

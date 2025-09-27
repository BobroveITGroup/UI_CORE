#pragma once
#include <Windows.h>
#include <string>

/// <summary>
/// Function types for working with a renderer DLL
/// </summary>
typedef void* (*tCreateRenderer)();
typedef void  (*tDestroyRenderer)(void*);
typedef void  (*tInitRenderer)(void*, HWND);
typedef void  (*tBeginDraw)(void*);
typedef void  (*tEndDraw)(void*);
typedef void  (*tClearFrame)(void*);
typedef void  (*tDrawLine)(void*, float x1, float y1, float x2, float y2, float r, float g, float b, float a, float thickness);
typedef void  (*tDrawRectangle)(void*, float x, float y, float w, float h, float r, float g, float b, float a, float thickness);
typedef void  (*tDrawCircle)(void*, float cx, float cy, float radius, float r, float g, float b, float a, float thickness);
typedef void  (*tDrawText_u)(void*, const char* text, float x, float y, float r, float g, float b, float a, float fontSize);
typedef void  (*tDrawPolygon)(void*, const float* points, size_t pointCount, float r, float g, float b, float a, float thickness);
typedef void  (*tSetViewportSize)(void*, float width, float height);

/// <summary>
/// Wrapper for a renderer DLL (Direct2D / OpenGL / Vulkan)
/// Provides a unified interface to interact with the renderer
/// without directly dealing with DLL function pointers.
/// </summary>
class RendererWrapper {
    HMODULE hDll = nullptr;      // Handle to the loaded DLL
    void* renderer = nullptr;    // Pointer to the renderer instance

    // DLL function pointers
    tCreateRenderer fnCreate = nullptr;
    tDestroyRenderer fnDestroy = nullptr;
    tInitRenderer fnInit = nullptr;
    tBeginDraw fnBegin = nullptr;
    tEndDraw fnEnd = nullptr;
    tClearFrame fnClear = nullptr;
    tDrawLine fnLine = nullptr;
    tDrawRectangle fnRect = nullptr;
    tDrawCircle fnCircle = nullptr;
    tDrawText_u fnText = nullptr;
    tDrawPolygon fnPolygon = nullptr;
    tSetViewportSize fnSetViewportSize = nullptr;

public:
    /// <summary>Load the DLL and retrieve all function pointers</summary>
    bool LoadDLL(const char* dllName);

    /// <summary>Initialize the renderer with a window handle (HWND)</summary>
    void Initialize(HWND hwnd);

    /// <summary>Begin a frame for rendering</summary>
    void Begin();

    /// <summary>End the current frame</summary>
    void End();

    /// <summary>Clear the current frame</summary>
    void Clear();

    /// <summary>Draw a line</summary>
    /// <param name="x1">X coordinate of the start point</param>
    /// <param name="y1">Y coordinate of the start point</param>
    /// <param name="x2">X coordinate of the end point</param>
    /// <param name="y2">Y coordinate of the end point</param>
    /// <param name="r">Red component (0..1)</param>
    /// <param name="g">Green component (0..1)</param>
    /// <param name="b">Blue component (0..1)</param>
    /// <param name="a">Alpha component (0..1)</param>
    /// <param name="thickness">Line thickness in pixels</param>
    void DrawLine(float x1, float y1, float x2, float y2, float r = 1.f, float g = 1.f, float b = 1.f,  float a = 1.f, float thickness = 1.f);

    /// <summary>Draw a rectangle</summary>
    /// <param name="x">X coordinate of the top-left corner</param>
    /// <param name="y">Y coordinate of the top-left corner</param>
    /// <param name="w">Width of the rectangle</param>
    /// <param name="h">Height of the rectangle</param>
    /// <param name="r">Red component (0..1)</param>
    /// <param name="g">Green component (0..1)</param>
    /// <param name="b">Blue component (0..1)</param>
    /// <param name="a">Alpha component (0..1)</param>
    /// <param name="thickness">Outline thickness (0 = filled)</param>
    void DrawRect(float x, float y, float w, float h, float r = 1.f, float g = 1.f, float b = 1.f, float a = 1.f, float thickness = 1.f);

    /// <summary>Draw a circle</summary>
    /// <param name="cx">X coordinate of the circle center</param>
    /// <param name="cy">Y coordinate of the circle center</param>
    /// <param name="radius">Radius of the circle</param>
    /// <param name="r">Red component (0..1)</param>
    /// <param name="g">Green component (0..1)</param>
    /// <param name="b">Blue component (0..1)</param>
    /// <param name="a">Alpha component (0..1)</param>
    /// <param name="thickness">Outline thickness (0 = filled)</param>
    void DrawCircle(float cx, float cy, float radius, float r = 1.f, float g = 1.f, float b = 1.f, float a = 1.f, float thickness = 1.f);

    /// <summary>Draw text</summary>
    /// <param name="text">Text string to draw</param>
    /// <param name="x">X coordinate of the text start</param>
    /// <param name="y">Y coordinate of the text baseline</param>
    /// <param name="r">Red component (0..1)</param>
    /// <param name="g">Green component (0..1)</param>
    /// <param name="b">Blue component (0..1)</param>
    /// <param name="a">Alpha component (0..1)</param>
    /// <param name="fontSize">Font size in pixels</param>
    void DrawText(const std::string& text, float x, float y, float r = 1.f, float g = 1.f, float b = 1.f, float a = 1.f, float fontSize = 16.f);

    /// <summary>
    /// Draw a polygon
    /// </summary>
    /// <param name="points">Array of coordinates [x0,y0, x1,y1, ...]</param>
    /// <param name="pointCount">Number of vertices (not number of array elements)</param>
    /// <param name="r,g,b,a">Color</param>
    /// <param name="thickness">Outline thickness (0 = filled)</param>
    void DrawPolygon(const float* points, size_t pointCount, float r = 1.f, float g = 1.f, float b = 1.f, float a = 1.f, float thickness = 1.f);

    /// <summary>
    /// Set the viewport size (usually on window resize)
    /// </summary>
    void SetViewportSize(float width, float height);

    /// <summary>Release all resources</summary>
    ~RendererWrapper();
};

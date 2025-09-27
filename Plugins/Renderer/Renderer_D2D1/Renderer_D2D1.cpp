#include "Renderer_D2D1.h"

#include <iostream>

using namespace UI_CORE;

/// <summary>
/// Initialize the Direct2D/DirectWrite rendering system with a given window handle.
/// This sets up COM, factories, and the render target.
/// </summary>
void Renderer_D2D1::InitializeRenderer(void* windowHandle)
{
    hwnd = static_cast<HWND>(windowHandle);

    // ===== 0. Initialize COM =====
    HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    if (FAILED(hr))
    {
        MessageBox(hwnd, L"Failed to initialize COM", L"Error", MB_OK | MB_ICONERROR);
        return;
    }

    // ===== 1. Create Direct2D factory =====
    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pFactory_d2d1);
    if (FAILED(hr) || !m_pFactory_d2d1)
    {
        MessageBox(hwnd, L"Failed to create D2D1 factory", L"Error", MB_OK | MB_ICONERROR);
        return;
    }

    // ===== 2. Create DirectWrite factory =====
    hr = DWriteCreateFactory(
        DWRITE_FACTORY_TYPE_SHARED,
        __uuidof(IDWriteFactory),
        reinterpret_cast<IUnknown**>(&m_pFactory_dwrite)
    );
    if (FAILED(hr) || !m_pFactory_dwrite)
    {
        MessageBox(hwnd, L"Failed to create DirectWrite factory", L"Error", MB_OK | MB_ICONERROR);
        return;
    }

    // ===== 3. Create WIC Imaging factory =====
    hr = CoCreateInstance(
        CLSID_WICImagingFactory,
        nullptr,
        CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(&m_pFactory_iwic)
    );
    if (FAILED(hr) || !m_pFactory_iwic)
    {
        MessageBox(hwnd, L"Failed to create WIC Imaging factory", L"Error", MB_OK | MB_ICONERROR);
        return;
    }

    // ===== 4. Create RenderTarget for the window =====
    RECT rc;
    GetClientRect(hwnd, &rc);

    D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

    D2D1_HWND_RENDER_TARGET_PROPERTIES hwndProps = {};
    hwndProps.hwnd = hwnd;
    hwndProps.pixelSize = size;
    hwndProps.presentOptions = D2D1_PRESENT_OPTIONS_NONE;

    D2D1_RENDER_TARGET_PROPERTIES rtProps = D2D1::RenderTargetProperties();

    hr = m_pFactory_d2d1->CreateHwndRenderTarget(
        rtProps,
        hwndProps,
        &m_pRenderTarget
    );

    if (FAILED(hr) || !m_pRenderTarget)
    {
        MessageBox(hwnd, L"Failed to create D2D RenderTarget", L"Error", MB_OK | MB_ICONERROR);
        return;
    }

    // ===== 5. Clear initial state =====
    m_pRenderTarget->BeginDraw();
    m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
    m_pRenderTarget->EndDraw();
}

/// <summary>
/// Shutdown the renderer and release all resources.
/// </summary>
void Renderer_D2D1::ShutdownRenderer()
{
    if (m_pRenderTarget)
    {
        m_pRenderTarget->EndDraw();
        m_pRenderTarget->Release();
        m_pRenderTarget = nullptr;
    }

    if (m_pFactory_d2d1)
    {
        m_pFactory_d2d1->Release();
        m_pFactory_d2d1 = nullptr;
    }

    if (m_pFactory_dwrite)
    {
        m_pFactory_dwrite->Release();
        m_pFactory_dwrite = nullptr;
    }

    if (m_pFactory_iwic)
    {
        m_pFactory_iwic->Release();
        m_pFactory_iwic = nullptr;
    }

    CoUninitialize();
}

/// <summary>
/// Clear the current frame.
/// </summary>
void Renderer_D2D1::ClearFrame()
{
    // TODO: Add implementation
}

/// <summary>
/// Render the current frame contents.
/// </summary>
void Renderer_D2D1::RenderFrame()
{
    // TODO: Add implementation
}

/// <summary>
/// Resize the render target to a new viewport size.
/// </summary>
void Renderer_D2D1::SetViewportSize(float width, float height)
{
    if (!m_pRenderTarget) {
        std::cerr << "[Renderer_D2D1] SetViewportSize: RenderTarget is null!\n";
        MessageBoxA(nullptr, "SetViewportSize: RenderTarget is null!", "Renderer_D2D1", MB_OK | MB_ICONERROR);
        return;
    }

    if (width == 0 || height == 0) {
        std::cerr << "[Renderer_D2D1] SetViewportSize: width or height is zero, skip resize\n";
        MessageBoxA(nullptr, "SetViewportSize: width or height is zero, skip resize", "Renderer_D2D1", MB_OK | MB_ICONWARNING);
        return;
    }

    HRESULT hr = m_pRenderTarget->Resize(D2D1::SizeU((UINT32)width, (UINT32)height));
    if (FAILED(hr)) {
        std::cerr << "[Renderer_D2D1] Resize failed! HRESULT = 0x" << std::hex << hr << "\n";
        MessageBoxA(nullptr, "Resize failed! Check console for HRESULT", "Renderer_D2D1", MB_OK | MB_ICONERROR);
    }
    else {
        std::cout << "[Renderer_D2D1] Resize succeeded: " << width << "x" << height << "\n";
    }
}

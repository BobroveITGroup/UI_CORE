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
#pragma comment (lib, "windowscodecs")

namespace UI_CORE
{
	typedef IPlugin_Renderer* RendererHandle;

	class Renderer_GDI : IPlugin_Renderer
	{
	public:
		virtual void InitializeRenderer(void* windowHandle) override;
		virtual void ShutdownRenderer() override;
		virtual void ClearFrame() override;
		virtual void RenderFrame() override;
		virtual void SetViewportSize(float width, float height) override;
		virtual void SubmitRenderCommand(void* command) override;
		virtual void Update() override;
		virtual void DrawLine(float x1, float y1, float x2, float y2, Color color, float thickness) override;
		virtual void DrawRectangle(float x, float y, float width, float height, Color color, float thickness) override;
		virtual void DrawCircle(float cx, float cy, float radius, Color color, float thickness) override;
		virtual void DrawText_u(const char* text, float x, float y, Color color, float fontSize) override;
		virtual void DrawRoundedRectangle(float x, float y, float width, float height, float radius, Color color, float thickness) override;
		virtual void DrawPolygon(const float* points, size_t pointCount, Color color, float thickness) override;
		virtual void DrawImage(ImageHandle* image, float x, float y, float width, float height, float alpha) override;
		virtual void DrawGradientRect(float x, float y, float width, float height, Gradient gradient) override;
		virtual void DrawShadow(float x, float y, float width, float height, Color color, float blurRadius) override;
		virtual void DrawBezier(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3, Color color, float thickness) override;
		virtual void SetClippingRect(float x, float y, float width, float height) override;
		virtual void ClearClipping() override;
		virtual void SetTransform(float translateX, float translateY, float scaleX, float scaleY, float rotationDeg) override;
		virtual void ResetTransform() override;
		virtual void SetBlendMode(int mode) override;
		virtual void SetTextAlignment(int alignment) override;
		virtual void SetTextWrapping(bool wrap) override;
		virtual void BeginDraw() override;
		virtual void EndDraw() override;

		virtual const char* GetName() { return "Renderer_GDI"; };
		virtual const char* GetAuthor() { return "Michael Bobrove "; };
		virtual const char* GetVersion() { return "0.0.1"; };
		virtual PluginType GetPluginType() { return PluginType::Renderer; };
		virtual void ShutdownPlugin();

		virtual void OnEvent(const Event& e);

	private:
		HWND hwnd;
		PAINTSTRUCT ps;
		HDC hdc;
	};
}

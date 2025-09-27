#pragma once

#include "IPlugin_UI.h"
#include "Wrap_Renderer.h"
#include "EventBus.h"
#include <vector>

namespace UI_CORE
{
    class UI_ColorBox : public IPlugin_UI
    {
    public:
        UI_ColorBox();

        const char* GetName() override { return "UI_ColorBox"; };
        const char* GetAuthor() override { return "Michael"; };
        const char* GetVersion() override { return "1.0.0"; };
        PluginType GetPluginType() override { return PluginType::UI; }

        // IPlugin_UI
        void ShutdownPlugin() override;
        void OnEvent(const Event& e) override;
        Size GetSize() override;
        void Init(EventBus* bus, RendererWrapper* renderer) override;
        void SetSize(float width, float height) override;
        Position GetPosition() override;
        void SetPosition(float x, float y) override;
        Padding GetPadding() override;
        void SetPadding(Padding_Type type, float value) override;
        void AddChild(IPlugin_UI* child) override;
        void RemoveChild(IPlugin_UI* child) override;
        bool GetVisible() override;
        void SetVisible(bool var) override;
        bool GetAvailable() override;
        void SetAvailable(bool var) override;

        // Render
        void Render();

    private:
        Size m_size;
        Position m_position;
        Padding m_padding;
        bool m_visible;
        bool m_available;

        EventBus* m_eventBus;
        RendererWrapper* m_renderer;

        std::vector<IPlugin_UI*> m_children;
    };
}

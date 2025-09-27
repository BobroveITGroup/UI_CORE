#include "UI_ColorBox.h"
#include "Wrap_Renderer.h" // optional wrapper to cast IPlugin_Renderer
#include <algorithm>

namespace UI_CORE
{
    // ==============================
    // UI_ColorBox: simple colored rectangle UI element
    // ==============================
    UI_ColorBox::UI_ColorBox()
        : m_size{ 100.f, 100.f },      // default width and height
          m_position{ 0.f, 0.f },      // default position
          m_padding{ 0.f, 0.f, 0.f, 0.f }, // default padding
          m_visible(true),             // visible by default
          m_available(true),           // available for interaction by default
          m_eventBus(nullptr),
          m_renderer(nullptr)
    {}

    /// <summary>
    /// Initialize the UI element with the event bus and renderer.
    /// </summary>
    void UI_ColorBox::Init(EventBus* bus, RendererWrapper* renderer)
    {
        m_eventBus = bus;
        m_renderer = renderer;
    }

    // ==============================
    // Size / Position / Padding
    // ==============================
    Size UI_ColorBox::GetSize() { return m_size; }
    void UI_ColorBox::SetSize(float width, float height) { m_size = { width, height }; }

    Position UI_ColorBox::GetPosition() { return m_position; }
    void UI_ColorBox::SetPosition(float x, float y) { m_position = { x, y }; }

    Padding UI_ColorBox::GetPadding() { return m_padding; }

    /// <summary>
    /// Set padding for the element (left, right, top, bottom).
    /// </summary>
    void UI_ColorBox::SetPadding(Padding_Type type, float value)
    {
        switch (type)
        {
        case Padding_Type::Left:   m_padding.left = value; break;
        case Padding_Type::Right:  m_padding.right = value; break;
        case Padding_Type::Top:    m_padding.top = value; break;
        case Padding_Type::Bottom: m_padding.bottom = value; break;
        }
    }

    // ==============================
    // Children Management
    // ==============================
    void UI_ColorBox::AddChild(IPlugin_UI* child)
    {
        if (child) m_children.push_back(child);
    }

    void UI_ColorBox::RemoveChild(IPlugin_UI* child)
    {
        m_children.erase(
            std::remove(m_children.begin(), m_children.end(), child),
            m_children.end()
        );
    }

    // ==============================
    // Visibility / Availability
    // ==============================
    bool UI_ColorBox::GetVisible() { return m_visible; }
    void UI_ColorBox::SetVisible(bool var) { m_visible = var; }

    bool UI_ColorBox::GetAvailable() { return m_available; }
    void UI_ColorBox::SetAvailable(bool var) { m_available = var; }

    // ==============================
    // Plugin lifecycle
    // ==============================
    void UI_ColorBox::ShutdownPlugin()
    {
        m_children.clear(); // free child elements
    }

    // ==============================
    // Event handling
    // ==============================
    void UI_ColorBox::OnEvent(const Event& e)
    {
        // TODO: handle events such as click, hover, etc.
    }

    // ==============================
    // Rendering
    // ==============================
    void UI_ColorBox::Render()
    {
        if (m_renderer)
        {
            // Draw a colored rectangle for this UI element
            m_renderer->DrawRect(
                m_position.x,
                m_position.y,
                m_size.width,
                m_size.height,
                0.2f, 0.6f, 0.9f, 1.0f, // RGBA color
                0.f                       // thickness (0 = filled)
            );
        }

        // Render all child elements
        for (auto& child : m_children)
        {
            child->Render();
        }
    }
}


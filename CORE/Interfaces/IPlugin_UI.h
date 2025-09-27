#pragma once

#include "IPlugin.h"
#include "EventBus.h"
#include "Renderer.h"

namespace UI_CORE
{
    /// <summary>
    /// Structure representing the size of a UI element.
    /// </summary>
    struct Size
    {
        float width;   ///< Width of the element
        float height;  ///< Height of the element
    };

    /// <summary>
    /// Structure representing the position of a UI element.
    /// </summary>
    struct Position
    {
        float x;  ///< X coordinate
        float y;  ///< Y coordinate
    };

    /// <summary>
    /// Specifies the padding type for a specific side.
    /// </summary>
    enum class Padding_Type
    {
        Left,
        Right,
        Top,
        Bottom
    };

    /// <summary>
    /// Structure representing padding around a UI element.
    /// </summary>
    struct Padding
    {
        float left;   ///< Left padding
        float top;    ///< Top padding
        float right;  ///< Right padding
        float bottom; ///< Bottom padding
    };

    /// <summary>
    /// Interface for UI element plugins.
    /// </summary>
    struct IPlugin_UI : public IPlugin
    {
        // =======================
        // ===== Size ============
        // =======================

        /// <summary>Gets the size of the UI element.</summary>
        /// <returns>A <see cref="Size"/> structure containing width and height.</returns>
        virtual Size GetSize() = 0;

        /// <summary>Initializes the UI element.</summary>
        /// <param name="bus">Pointer to the shared <see cref="EventBus"/> instance.</param>
        /// <param name="renderer">Pointer to the <see cref="RendererWrapper"/> instance.</param>
        virtual void Init(EventBus* bus, RendererWrapper* renderer) = 0;

        /// <summary>Sets the size of the UI element.</summary>
        /// <param name="width">Width in pixels.</param>
        /// <param name="height">Height in pixels.</param>
        virtual void SetSize(float width, float height) = 0;

        // =======================
        // ===== Position =======
        // =======================

        /// <summary>Gets the position of the UI element.</summary>
        /// <returns>A <see cref="Position"/> structure containing X and Y coordinates.</returns>
        virtual Position GetPosition() = 0;

        /// <summary>Sets the position of the UI element.</summary>
        /// <param name="x">X coordinate.</param>
        /// <param name="y">Y coordinate.</param>
        virtual void SetPosition(float x, float y) = 0;

        // =======================
        // ===== Padding ========
        // =======================

        /// <summary>Gets the padding of the UI element.</summary>
        /// <returns>A <see cref="Padding"/> structure with all padding values.</returns>
        virtual Padding GetPadding() = 0;

        /// <summary>Sets the padding value for a specific side.</summary>
        /// <param name="type">The side of the element (Left, Right, Top, Bottom).</param>
        /// <param name="value">Padding value in pixels.</param>
        virtual void SetPadding(Padding_Type type, float value) = 0;

        // =======================
        // ===== Child Elements ==
        // =======================

        /// <summary>Adds a child UI element.</summary>
        /// <param name="child">Pointer to the child <see cref="IPlugin_UI"/> element.</param>
        virtual void AddChild(IPlugin_UI* child) = 0;

        /// <summary>Removes a child UI element.</summary>
        /// <param name="child">Pointer to the child <see cref="IPlugin_UI"/> element.</param>
        virtual void RemoveChild(IPlugin_UI* child) = 0;

        // =======================
        // ===== Visibility ======
        // =======================

        /// <summary>Gets the visibility state of the UI element.</summary>
        /// <returns>true if visible; otherwise, false.</returns>
        virtual bool GetVisible() = 0;

        /// <summary>Sets the visibility of the UI element.</summary>
        /// <param name="var">true = visible, false = hidden.</param>
        virtual void SetVisible(bool var) = 0;

        // =======================
        // ===== Availability ====
        // =======================

        /// <summary>Gets whether the UI element is available for interaction.</summary>
        /// <returns>true if available; otherwise, false.</returns>
        virtual bool GetAvailable() = 0;

        /// <summary>Sets the availability of the UI element.</summary>
        /// <param name="var">true = available, false = unavailable.</param>
        virtual void SetAvailable(bool var) = 0;

        // =======================
        // ===== Rendering =======
        // =======================

        /// <summary>Renders the UI element.</summary>
        virtual void Render() = 0;
    };
}

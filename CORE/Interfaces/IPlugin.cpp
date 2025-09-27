#pragma once
#include <cstdint>
#include <cstddef>
#include "EventBus.h"

namespace UI_CORE
{
    struct Event;

    /// <summary>
    /// Defines the type of a plugin.
    /// </summary>
    enum class PluginType : uint8_t
    {
        Unknown = 0,
        UI,
        Algorithm,
        Renderer,
        Input,
        Audio,
        Network,
        Physics,
        Tools,
        AI,
        Script,
        Data,
        Platform,
        EventBus
    };

    /// <summary>
    /// Abstract interface for a plugin.
    /// Each plugin receives a pointer to the <see cref="EventBus"/> for sending and receiving events.
    /// </summary>
    struct IPlugin
    {
        virtual ~IPlugin() = default;

        // =======================
        // ===== Basic Info ======
        // =======================

        /// <summary>
        /// Gets the name of the plugin.
        /// </summary>
        /// <returns>Plugin name as a null-terminated string.</returns>
        virtual const char* GetName() = 0;

        /// <summary>
        /// Gets the author of the plugin.
        /// </summary>
        /// <returns>Plugin author as a null-terminated string.</returns>
        virtual const char* GetAuthor() = 0;

        /// <summary>
        /// Gets the version of the plugin.
        /// </summary>
        /// <returns>Plugin version as a null-terminated string.</returns>
        virtual const char* GetVersion() = 0;

        /// <summary>
        /// Gets the type of the plugin.
        /// </summary>
        /// <returns>A value from the <see cref="PluginType"/> enum.</returns>
        virtual PluginType GetPluginType() = 0;

        // =======================
        // ===== Lifecycle =======
        // =======================

        /// <summary>
        /// Initializes the plugin.
        /// </summary>
        /// <param name="bus">Pointer to the shared <see cref="EventBus"/> instance used for event communication.</param>
        virtual void InitializePlugin(EventBus* bus)
        {
            eventBus = bus;
        }

        /// <summary>
        /// Shuts down the plugin.
        /// </summary>
        virtual void ShutdownPlugin() = 0;

        // =======================
        // ===== EventBus ========
        // =======================

        /// <summary>
        /// Sends an event to the EventBus.
        /// </summary>
        /// <param name="e">The event to send.</param>
        virtual void SendEvent(const Event& e)
        {
            if (eventBus)
                eventBus->Publish(e);
        }

        /// <summary>
        /// Subscribes to events of a specific type.
        /// </summary>
        /// <param name="eventType">The name of the event type to subscribe to.</param>
        virtual void SubscribeEvent(const char* eventType)
        {
            if (eventBus)
                eventBus->Subscribe(eventType, this);
        }

        /// <summary>
        /// Unsubscribes from events of a specific type.
        /// </summary>
        /// <param name="eventType">The name of the event type to unsubscribe from.</param>
        virtual void UnsubscribeEvent(const char* eventType)
        {
            if (eventBus)
                eventBus->Unsubscribe(eventType, this);
        }

        /// <summary>
        /// Called by the EventBus when an event is received.
        /// </summary>
        /// <param name="e">The event to handle.</param>
        virtual void OnEvent(const Event& e) = 0;

    protected:
        EventBus* eventBus = nullptr; ///< Pointer to the shared EventBus instance
    };
}

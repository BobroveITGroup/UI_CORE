#pragma once
#include <cstdint>
#include <cstddef>
#include <cstring>
#include <algorithm>

#define _CRT_SECURE_NO_WARNINGS

namespace UI_CORE
{
    struct IPlugin; ///< Forward declaration of plugin interface

    // =======================
    // ===== Constants =======
    // =======================

    constexpr size_t MAX_EVENTS = 1024;               ///< Maximum number of queued events
    constexpr size_t EVENT_TYPE_SIZE = 64;           ///< Maximum length of event type string
    constexpr size_t EVENT_DATA_SIZE = 256;          ///< Maximum size of event payload in bytes
    constexpr size_t MAX_SUBSCRIBERS_PER_TYPE = 16;  ///< Maximum subscribers per event type
    constexpr size_t MAX_EVENT_TYPES = 1000;         ///< Maximum number of different event types

    // =======================
    // ===== Event Struct =====
    // =======================

    /// <summary>
    /// Represents a single event in the EventBus system.
    /// </summary>
    struct Event
    {
        IPlugin* sender;                     ///< Plugin sending the event
        IPlugin* receiver;                   ///< Optional specific receiver (nullptr = broadcast)
        char type[EVENT_TYPE_SIZE];          ///< Event type identifier
        uint8_t data[EVENT_DATA_SIZE];       ///< Raw event data
        size_t dataSize;                     ///< Size of the data payload
    };

    // =======================
    // ===== Subscriber List ==
    // =======================

    /// <summary>
    /// List of subscribers for a single event type.
    /// </summary>
    struct EventSubscriberList
    {
        IPlugin* subscribers[MAX_SUBSCRIBERS_PER_TYPE]{}; ///< Array of subscribers
        size_t count = 0;                                 ///< Number of active subscribers

        /// <summary>Adds a subscriber to the list.</summary>
        /// <param name="p">Pointer to the subscriber plugin.</param>
        /// <returns>true if added successfully, false if full or already exists.</returns>
        bool Add(IPlugin* p);

        /// <summary>Removes a subscriber from the list.</summary>
        /// <param name="p">Pointer to the subscriber plugin.</param>
        void Remove(IPlugin* p);
    };

    // =======================
    // ===== Event Type Entry =
    // =======================

    /// <summary>
    /// Represents a registered event type and its subscribers.
    /// </summary>
    struct EventTypeEntry
    {
        char type[EVENT_TYPE_SIZE]{}; ///< Event type identifier
        EventSubscriberList list;     ///< Subscribers for this event type
    };

    // =======================
    // ===== Event Bus =======
    // =======================

    /// <summary>
    /// Core EventBus system for sending and receiving events between plugins.
    /// </summary>
    class EventBus
    {
    public:
        /// <summary>Constructs an empty EventBus.</summary>
        EventBus();

        /// <summary>Subscribes a plugin to a specific event type.</summary>
        /// <param name="type">Event type string.</param>
        /// <param name="plugin">Plugin to subscribe.</param>
        void Subscribe(const char* type, IPlugin* plugin);

        /// <summary>Unsubscribes a plugin from a specific event type.</summary>
        /// <param name="type">Event type string.</param>
        /// <param name="plugin">Plugin to unsubscribe.</param>
        void Unsubscribe(const char* type, IPlugin* plugin);

        /// <summary>Publishes an event to the EventBus.</summary>
        /// <param name="e">Event to publish.</param>
        /// <returns>true if the event was queued successfully.</returns>
        bool Publish(const Event& e);

        /// <summary>Checks if there are pending events in the queue.</summary>
        /// <returns>true if events are available.</returns>
        bool HasEvents() const;

        /// <summary>Clears the event queue.</summary>
        void ClearQueue();

        /// <summary>Processes all queued events and dispatches them to subscribers.</summary>
        void ProcessEvents();

    private:
        /// <summary>Dispatches an event to its subscribers.</summary>
        /// <param name="e">Event to dispatch.</param>
        void Dispatch(const Event& e);

        /// <summary>Pops the next event from the queue.</summary>
        /// <param name="out">Reference to store the popped event.</param>
        /// <returns>true if an event was popped.</returns>
        bool Pop(Event& out);

        /// <summary>Finds an existing event type entry.</summary>
        /// <param name="type">Event type string.</param>
        /// <returns>Pointer to the entry, or nullptr if not found.</returns>
        EventTypeEntry* FindType(const char* type);

        /// <summary>Finds or creates an event type entry.</summary>
        /// <param name="type">Event type string.</param>
        /// <returns>Pointer to the entry.</returns>
        EventTypeEntry* FindOrCreateType(const char* type);

    private:
        Event events[MAX_EVENTS];          ///< Circular buffer for queued events
        size_t head;                       ///< Head index of the queue
        size_t tail;                       ///< Tail index of the queue

        EventTypeEntry types[MAX_EVENT_TYPES]; ///< Registered event types
        size_t typeCount;                       ///< Number of active event types
    };
}

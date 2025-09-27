#include "EventBus.h"
#include "IPlugin.h" // Full definition of IPlugin

#include <iostream>
#include <cstring>

namespace UI_CORE
{
    // ============================
    // ===== EventSubscriberList ===
    // ============================

    /// <summary>Adds a plugin to the subscriber list.</summary>
    /// <param name="p">Plugin pointer.</param>
    /// <returns>true if successfully added, false if full or duplicate.</returns>
    bool EventSubscriberList::Add(IPlugin* p)
    {
        if (count >= MAX_SUBSCRIBERS_PER_TYPE) {
            std::cerr << "[EventBus] Error: Too many subscribers for event.\n";
            return false;
        }
        subscribers[count++] = p;
        std::cout << "[EventBus] Subscriber added (" << count << " total)\n";
        return true;
    }

    /// <summary>Removes a plugin from the subscriber list.</summary>
    /// <param name="p">Plugin pointer.</param>
    void EventSubscriberList::Remove(IPlugin* p)
    {
        for (size_t i = 0; i < count; ++i)
        {
            if (subscribers[i] == p)
            {
                subscribers[i] = subscribers[--count];
                std::cout << "[EventBus] Subscriber removed (" << count << " total)\n";
                return;
            }
        }
        std::cout << "[EventBus] Attempted to remove a plugin not subscribed.\n";
    }

    // ============================
    // ===== EventBus =============
    // ============================

    /// <summary>Constructs an empty EventBus.</summary>
    EventBus::EventBus() : head(0), tail(0), typeCount(0)
    {
        std::cout << "[EventBus] Event bus created.\n";
    }

    /// <summary>Subscribes a plugin to a given event type.</summary>
    void EventBus::Subscribe(const char* type, IPlugin* plugin)
    {
        EventTypeEntry* entry = FindOrCreateType(type);
        if (entry) {
            entry->list.Add(plugin);
            std::cout << "[EventBus] Subscribed to event type: " << type << "\n";
        }
    }

    /// <summary>Unsubscribes a plugin from a given event type.</summary>
    void EventBus::Unsubscribe(const char* type, IPlugin* plugin)
    {
        EventTypeEntry* entry = FindType(type);
        if (entry) {
            entry->list.Remove(plugin);
            std::cout << "[EventBus] Unsubscribed from event type: " << type << "\n";
        }
    }

    /// <summary>Publishes an event to the event queue.</summary>
    /// <returns>true if queued successfully, false if queue is full.</returns>
    bool EventBus::Publish(const Event& e)
    {
        size_t nextHead = (head + 1) % MAX_EVENTS;
        if (nextHead == tail) {
            std::cerr << "[EventBus] Event queue overflow! Event '" << e.type << "' lost.\n";
            return false;
        }
        events[head] = e;
        head = nextHead;
        std::cout << "[EventBus] Event published: " << e.type << "\n";
        return true;
    }

    /// <summary>Checks if there are pending events in the queue.</summary>
    bool EventBus::HasEvents() const
    {
        return head != tail;
    }

    /// <summary>Clears all queued events.</summary>
    void EventBus::ClearQueue()
    {
        head = tail = 0;
        std::cout << "[EventBus] Event queue cleared.\n";
    }

    /// <summary>Processes all queued events and dispatches them.</summary>
    void EventBus::ProcessEvents()
    {
        Event e;
        while (Pop(e))
        {
            std::cout << "[EventBus] Processing event: " << e.type << "\n";
            Dispatch(e);
        }
    }

    /// <summary>Dispatches an event to its receiver(s).</summary>
    void EventBus::Dispatch(const Event& e)
    {
        if (e.receiver) // Direct dispatch
        {
            std::cout << "[EventBus] Direct dispatch: " << e.type << "\n";
            e.receiver->OnEvent(e);
        }
        else // Broadcast
        {
            EventTypeEntry* entry = FindType(e.type);
            if (!entry) {
                std::cout << "[EventBus] No subscribers for event: " << e.type << "\n";
                return;
            }
            std::cout << "[EventBus] Broadcasting event: " << e.type
                      << " (" << entry->list.count << " subscribers)\n";
            for (size_t i = 0; i < entry->list.count; ++i)
            {
                IPlugin* plugin = entry->list.subscribers[i];
                if (plugin) plugin->OnEvent(e);
            }
        }
    }

    /// <summary>Pops the next event from the queue.</summary>
    /// <returns>true if an event was popped.</returns>
    bool EventBus::Pop(Event& out)
    {
        if (tail == head) return false;
        out = events[tail];
        tail = (tail + 1) % MAX_EVENTS;
        return true;
    }

    /// <summary>Finds an existing event type entry.</summary>
    EventTypeEntry* EventBus::FindType(const char* type)
    {
        for (size_t i = 0; i < typeCount; ++i)
        {
            if (strncmp(types[i].type, type, EVENT_TYPE_SIZE) == 0)
                return &types[i];
        }
        return nullptr;
    }

    /// <summary>Finds or creates a new event type entry.</summary>
    EventTypeEntry* EventBus::FindOrCreateType(const char* type)
    {
        EventTypeEntry* entry = FindType(type);
        if (entry) return entry;

        if (typeCount >= MAX_EVENT_TYPES) {
            std::cerr << "[EventBus] Error: Maximum number of event types reached.\n";
            return nullptr;
        }

        strncpy_s(types[typeCount].type, EVENT_TYPE_SIZE, type, _TRUNCATE);
        types[typeCount].type[EVENT_TYPE_SIZE - 1] = '\0';
        std::cout << "[EventBus] New event type created: " << types[typeCount].type << "\n";

        return &types[typeCount++];
    }
}

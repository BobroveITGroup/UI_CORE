#include "BaseClass.h"
#include <cstring> // strcmp

extern "C" {

    //========================
    // EventBus
    //========================
    EventBus* EventBus_Create(int capacity)
    {
        return new EventBus(capacity);
    }

    void EventBus_Destroy(EventBus* bus)
    {
        delete bus;
    }

    void EventBus_Subscribe(EventBus* bus, const char* eventName, IEventHandler* handler)
    {
        if (bus && handler)
            bus->Subscribe(eventName, handler);
    }

    void EventBus_Trigger(EventBus* bus, const char* eventName)
    {
        if (bus)
            bus->Trigger(eventName);
    }

    //========================
    // UI_2D_Element
    //========================
    UI_2D_Element* UI2D_CreateElement(UI_2D_Element* element)
    {
        return element; // просто возвращаем указатель, реальное создание делаем через конструктор наследника
    }

    void UI2D_DestroyElement(UI_2D_Element* element)
    {
        if (element)
            element->Destroy(); // сам вызовет delete
    }

    void UI2D_SetPosition(UI_2D_Element* element, float x, float y)
    {
        if (element) element->SetPosition(x, y);
    }

    void UI2D_SetSize(UI_2D_Element* element, float w, float h)
    {
        if (element) element->SetSize(w, h);
    }

    void UI2D_SetPadding(UI_2D_Element* element, Padding p, float val)
    {
        if (element) element->SetPadding(p, val);
    }

    void UI2D_SetVisible(UI_2D_Element* element, bool v)
    {
        if (element) element->SetVisible(v);
    }

    void UI2D_SetAvailable(UI_2D_Element* element, bool v)
    {
        if (element) element->SetAvailable(v);
    }

    void UI2D_SetEventHandler(UI_2D_Element* element, IEventHandler* handler)
    {
        if (element) element->SetEventHandler(handler);
    }

    void UI2D_TriggerEvent(UI_2D_Element* element, const char* name)
    {
        if (element) element->TriggerEvent(name);
    }

    //========================
    // HitTest
    //========================
    bool UI2D_HitTest(UI_2D_Element* element, float px, float py)
    {
        if (!element) return false;
        return element->HitTest(px, py);
    }

} // extern "C"

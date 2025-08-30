#pragma once

#include <d2d1.h>
#include <cstring> // для strcmp

//======================================================
// Основной комментарий по архитектуре
//======================================================
//
// UI_2D_Element — базовый класс всех визуальных элементов UI.
// Каждый элемент может:
//   - Иметь размеры, позицию и паддинги
//   - Отрисовываться на Direct2D-рендере
//   - Обрабатывать события ввода (мышь, клавиши)
//   - Проверять попадание курсора (HitTest)
//   - Взаимодействовать с EventBus через IEventHandler
//
// EventBus обеспечивает простой обмен событиями между элементами.
// Подписчики регистрируются на определённые имена событий.
// При вызове Trigger(eventName) все подписчики соответствующего события получают уведомление.
// EventBus реализован без STL, полностью безопасен для использования в DLL.
//

//------------------------------------------------------
// Перечисления для настроек элементов
//------------------------------------------------------
enum Padding { left = 0, right = 1, top = 2, bottom = 3 };
enum class StretchMode { None, Horizontal, Vertical, Both };

//------------------------------------------------------
// Интерфейс обработчика событий
//------------------------------------------------------
struct IEventHandler {
    virtual ~IEventHandler() {}
    virtual void OnEvent(const char* name) = 0; // вызывается при событии
};

//------------------------------------------------------
// Структура подписчика EventBus
//------------------------------------------------------
struct Subscriber {
    IEventHandler* handler;  // указатель на объект-обработчик
    const char* eventName;   // имя события, на которое подписан
};

//------------------------------------------------------
// Простая реализация EventBus без STL
//------------------------------------------------------
class EventBus {
    Subscriber* subscribers; // массив подписчиков
    int count;               // текущее количество подписок
    int capacity;            // максимальное количество подписок

public:
    EventBus(int cap = 100)
        : count(0), capacity(cap)
    {
        subscribers = new Subscriber[capacity]; // выделяем память под подписчиков
    }

    ~EventBus() { delete[] subscribers; }

    // Подписка на событие
    void Subscribe(const char* eventName, IEventHandler* h) {
        if (count < capacity) {
            subscribers[count++] = { h, eventName };
        }
    }

    // Вызов события
    void Trigger(const char* eventName) {
        for (int i = 0; i < count; ++i) {
            if (strcmp(subscribers[i].eventName, eventName) == 0) {
                subscribers[i].handler->OnEvent(eventName);
            }
        }
    }
};

//======================================================
// Базовый UI-элемент
//======================================================
class UI_2D_Element {
public:
    UI_2D_Element()
        : width_min(1), height_min(1),
        width_max(100000), height_max(100000),
        width(0), height(0), x(0), y(0),
        padding_left(0), padding_right(0), padding_top(0), padding_bottom(0),
        isVisible(true), isAvailable(true),
        Stretch_Mode_(StretchMode::None),
        handler(nullptr),
        elementId(0)
    {}

    virtual ~UI_2D_Element() {}

    //--------------------------------------------------
    // Жизненный цикл
    //--------------------------------------------------
    virtual void Destroy() { delete this; }

    //--------------------------------------------------
    // Базовая информация
    //--------------------------------------------------
    virtual const char* GetElementType() const = 0; // возвращает тип элемента

    //--------------------------------------------------
    // Логика / отрисовка
    //--------------------------------------------------
    virtual void Update(float deltaTime) {} // обновление логики
    virtual HRESULT Render(ID2D1HwndRenderTarget* RT, IUnknown** resources, size_t resourceCount) = 0;

    //--------------------------------------------------
    // Проверка попадания курсора (HitTest)
    //--------------------------------------------------
    bool HitTest(float px, float py) const {
        return isVisible && isAvailable &&
            px >= x && px <= x + width &&
            py >= y && py <= y + height;
    }

    //--------------------------------------------------
    // Размеры
    //--------------------------------------------------
    void SetMinSize(float _w, float _h) { width_min = _w; height_min = _h; }
    void SetMaxSize(float _w, float _h) { width_max = _w; height_max = _h; }
    void SetSize(float _w, float _h) {
        width = (_w < width_min) ? width_min : (_w > width_max ? width_max : _w);
        height = (_h < height_min) ? height_min : (_h > height_max ? height_max : _h);
    }

    //--------------------------------------------------
    // Позиция
    //--------------------------------------------------
    void SetPosition(float _x, float _y) { x = _x; y = _y; }

    //--------------------------------------------------
    // Паддинги
    //--------------------------------------------------
    void SetPadding(Padding padding, float var) {
        switch (padding) {
        case left: padding_left = var; break;
        case right: padding_right = var; break;
        case top: padding_top = var; break;
        case bottom: padding_bottom = var; break;
        }
    }

    //--------------------------------------------------
    // Флаги видимости и доступности
    //--------------------------------------------------
    void SetVisible(bool var) { isVisible = var; }
    void SetAvailable(bool var) { isAvailable = var; }

    //--------------------------------------------------
    // Связь с EventBus через обработчик
    //--------------------------------------------------
    void SetEventHandler(IEventHandler* h) { handler = h; }
    void TriggerEvent(const char* name) { if (handler) handler->OnEvent(name); }

protected:
    // Минимальные и максимальные размеры
    float width_min, width_max;
    float height_min, height_max;

    // Текущие размеры и позиция
    float width, height;
    float x, y;

    // Паддинги
    float padding_left, padding_right, padding_top, padding_bottom;

    // Флаги состояния
    bool isVisible;
    bool isAvailable;
    bool hovered = false;
    bool pressed = false;
    bool isFocused = false;

    // Режим растягивания
    StretchMode Stretch_Mode_;

    // EventBus-обработчик (можно один для всех элементов)
    IEventHandler* handler;

    // Уникальный ID элемента
    unsigned long long elementId;
};

#pragma once
#include <list>
#include <map>
#include <typeindex>
#include "Graphics/View.h"

class Event
{
protected:
    virtual ~Event() {};
};

class HandlerFunctionBase
{
public:
    void Exec(Event* evnt); 
private:
    virtual void Call(Event* evnt) = 0;
};

template <class T, class EventType>
class MemberFunctionHandler : public HandlerFunctionBase
{
public:
    typedef void (T::* MemberFunction) (EventType*);
    MemberFunctionHandler(T* instance, MemberFunction member_function)
    {
        m_instance = instance;
        m_member_function = member_function;
    }

    void Call(Event* evnt)
    {
        (m_instance->*m_member_function)(static_cast<EventType*>(evnt));
    }

private:
    T* m_instance;
    MemberFunction m_member_function;
};

typedef std::list<HandlerFunctionBase*> HandlerList;

class EventBus
{
public:
    template <typename EventType>
    static void Publish(EventType* evnt)
    {
        HandlerList* handlers = subscribers[typeid(EventType)];

        if (handlers == nullptr)
            return;

        for (auto& handler : *handlers)
        {
            if (handler != nullptr)
            {
                handler->Exec(evnt);
            }
        }
    }


    template <class T, class EventType>
    static void Subscribe(T* instance, void (T::* member_function)(EventType*))
    {
        HandlerList* handlers = subscribers[typeid(EventType)];
        if (handlers == nullptr)
        {
            handlers = new HandlerList();
            subscribers[typeid(EventType)] = handlers;
        }
        handlers->push_back(new MemberFunctionHandler<T, EventType>(instance, member_function));
    }

private:
    static std::map<std::type_index, HandlerList*> subscribers;
};

struct ApplicationInitEvent : public Event 
{
    ApplicationInitEvent(const char* ti, int w, int h) : title (ti), width(w), height(h) {}
    const char* title;
    int width, height;
};
struct SceneBeginEvent : public Event
{

};
struct CloseEvent : public Event {};

struct UpdateEvent : public Event
{
    UpdateEvent (float dt) : deltaTime(dt) {}
    float deltaTime;
};  

struct DrawEvent : public Event
{
    DrawEvent(View* vi) : view(vi) {}
    View* view;
};



struct InputEvent : public Event
{

}; 


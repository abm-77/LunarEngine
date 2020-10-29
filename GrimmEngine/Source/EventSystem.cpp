#include "System/EventSystem.h"

void HandlerFunctionBase::Exec(Event* evnt)
{
    Call(evnt);
}


std::map<std::type_index, HandlerList*> EventBus::subscribers;
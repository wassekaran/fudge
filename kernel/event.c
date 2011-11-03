#include <lib/memory.h>
#include <kernel/event.h>
#include <kernel/vfs.h>
#include <kernel/runtime.h>

struct event_event eventHandlers[32];

void event_register(unsigned int index, unsigned int id, void (*handler)())
{

    if (eventHandlers[index].id != 0)
        return;

    eventHandlers[index].id = id;
    eventHandlers[index].handler = handler;

}

void event_unregister(unsigned int index, unsigned int id)
{

    if (eventHandlers[index].id != id)
        return;

    eventHandlers[index].id = 0;

}

struct event_event *event_get(unsigned int index)
{

    return &eventHandlers[index];

}

unsigned int event_handler(unsigned int index)
{

    struct event_event *event = event_get(index);

    if (!(event && event->id))
        return 0;

    struct runtime_task *task = runtime_get_running_task();

    if (!task)
        return 0;

    struct runtime_task *oldtask = runtime_get_task(event->id);

    if (!oldtask)
        return 0;

    oldtask->parentid = task->id;
    oldtask->registers.ip = event->handler;

    runtime_activate(oldtask);

    return 1;

}

void event_init()
{

}


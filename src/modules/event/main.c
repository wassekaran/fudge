#include <fudge.h>
#include <kernel.h>
#include <event/event.h>
#include <modules/system/system.h>
#include "event.h"

static struct system_node root;

unsigned int event_unicast(struct list *states, struct event_header *header, unsigned int count)
{

    struct list_item *current;

    spinlock_acquire(&states->spinlock);

    for (current = states->head; current; current = current->next)
    {

        struct service_state *state = current->data;

        if (header->destination != state->task->id)
            continue;

        kernel_writemailbox(state->task, header, count);
        kernel_unblocktask(state->task);

    }

    spinlock_release(&states->spinlock);

    return count;

}

unsigned int event_multicast(struct list *states, struct event_header *header, unsigned int count)
{

    struct list_item *current;

    spinlock_acquire(&states->spinlock);

    for (current = states->head; current; current = current->next)
    {

        struct service_state *state = current->data;

        header->destination = state->task->id;

        kernel_writemailbox(state->task, header, count);
        kernel_unblocktask(state->task);

    }

    spinlock_release(&states->spinlock);

    return count;

}

unsigned int event_send(struct list *states, struct service_state *state, void *buffer, unsigned int count)
{

    struct event_header *header = buffer;

    header->source = state->task->id;

    if (header->destination)
        return event_unicast(states, header, count);
    else
        return event_multicast(states, header, count);

}

void module_init(void)
{

    system_initnode(&root, SYSTEM_NODETYPE_MAILBOX, "event");

}

void module_register(void)
{

    system_registernode(&root);

}

void module_unregister(void)
{

    system_unregisternode(&root);

}


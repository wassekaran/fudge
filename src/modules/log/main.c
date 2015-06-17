#include <fudge.h>
#include <kernel.h>
#include <modules/system/system.h>
#include "log.h"

static struct system_node root;
static struct system_node critical;
static struct system_node error;
static struct system_node warning;
static struct system_node info;

void log_notify(unsigned int level, unsigned int size, unsigned int count, void *buffer)
{

    if (level <= LOG_CRITICAL)
        rendezvous_writelist(&critical.mailboxes, size, count, buffer);

    if (level <= LOG_ERROR)
        rendezvous_writelist(&error.mailboxes, size, count, buffer);

    if (level <= LOG_WARNING)
        rendezvous_writelist(&warning.mailboxes, size, count, buffer);

    if (level <= LOG_INFO)
        rendezvous_writelist(&info.mailboxes, size, count, buffer);

}

void module_init()
{

    system_initnode(&root, SYSTEM_NODETYPE_GROUP, "log");
    system_initnode(&critical, SYSTEM_NODETYPE_MAILBOX, "critical");
    system_addchild(&root, &critical);
    system_initnode(&error, SYSTEM_NODETYPE_MAILBOX, "error");
    system_addchild(&root, &error);
    system_initnode(&warning, SYSTEM_NODETYPE_MAILBOX, "warning");
    system_addchild(&root, &warning);
    system_initnode(&info, SYSTEM_NODETYPE_MAILBOX, "info");
    system_addchild(&root, &info);

}

void module_register()
{

    system_registernode(&root);

}

void module_unregister()
{

    system_unregisternode(&root);

}

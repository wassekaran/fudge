#include <fudge/memory.h>
#include <base/base.h>
#include "net.h"

void net_init_protocol(struct net_protocol *protocol, char *name, unsigned int (*read)(struct net_interface *interface, unsigned int offset, unsigned int count, void *buffer), unsigned int (*write)(struct net_interface *interface, unsigned int offset, unsigned int count, void *buffer))
{

    memory_clear(protocol, sizeof (struct net_protocol));

    protocol->name = name;
    protocol->read = read;
    protocol->write = write;

}


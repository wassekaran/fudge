#include <fudge/module.h>
#include <base/base.h>
#include <base/network.h>
#include "ipv6.h"

static struct base_network_protocol protocol;

void init()
{

    ipv6_init_protocol(&protocol);
    base_network_register_protocol(0x86DD, &protocol);

}

void destroy()
{

}

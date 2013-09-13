#include <fudge/module.h>
#include <fudge/define.h>
#include <fudge/data/circular.h>
#include <system/system.h>
#include <base/base.h>
#include <base/keyboard.h>
#include <mouse/mouse.h>
#include "ps2.h"

void ps2_init_device(struct ps2_device *device, struct ps2_bus *bus, unsigned int irq)
{

    memory_clear(device, sizeof (struct ps2_device));
    base_init_device(&device->base, PS2_DEVICE_TYPE, irq, "ps2", &bus->base);

}


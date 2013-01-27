#include <fudge/module.h>
#include <system/system.h>
#include <base/base.h>
#include <block/block.h>
#include "atapi.h"

static struct atapi_driver driver;

void init()
{

    atapi_init_driver(&driver);
    base_register_driver(&driver.base);
    block_register_interface(&driver.interface);

}

void destroy()
{

    block_unregister_interface(&driver.interface);
    base_unregister_driver(&driver.base);

}

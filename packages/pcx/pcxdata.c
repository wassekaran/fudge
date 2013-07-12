#include <fudge.h>
#include <gfx/gfx.h>
#include <gfx/pcx.h>

static struct pcx_surface pcx;

void main()
{

    pcx_init_surface(&pcx, CALL_DI);
    pcx_load(&pcx);
    gfx_write_surface(CALL_DO, &pcx.base);

}

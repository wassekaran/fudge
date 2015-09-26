#include <abi.h>
#include <fudge.h>
#include "box.h"
#include "renderable.h"

static void (*renderers[16])(struct renderable *renderable, struct ctrl_videosettings *settings, void *drawdata, void *fontdata, unsigned int line);

void renderable_register(unsigned int type, void (*renderer)(struct renderable *renderable, struct ctrl_videosettings *settings, void *drawdata, void *fontdata, unsigned int line))
{

    renderers[type] = renderer;

}

void renderable_render(struct renderable *renderable, struct ctrl_videosettings *settings, void *drawdata, void *fontdata, unsigned int line)
{

    if (line < renderable->size.y || line >= renderable->size.y + renderable->size.h)
        return;

    if (!renderable->visible)
        return;

    renderers[renderable->type](renderable, settings, drawdata, fontdata, line);

}

void renderable_init(struct renderable *renderable, unsigned int type, unsigned int count)
{

    list_inititem(&renderable->item, renderable);

    renderable->type = type;
    renderable->count = count;

}

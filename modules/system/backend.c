#include <fudge/module.h>
#include <kernel/vfs.h>
#include "system.h"
#include "backend.h"

static unsigned int backend_read(struct vfs_backend *self, unsigned int offset, unsigned int count, void *buffer)
{

    return memory_read(buffer, count, "FUDGE_SYSTEM", 12, offset);

}

static unsigned int backend_write(struct vfs_backend *self, unsigned int offset, unsigned int count, void *buffer)
{

    return 0;

}

void system_init_backend(struct system_backend *backend)
{

    memory_clear(backend, sizeof (struct system_backend));
    vfs_init_backend(&backend->base, backend_read, backend_write);
    system_init_group(&backend->root, "/");

    backend->root.node.parent = &backend->root.node;

}

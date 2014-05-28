#include <module.h>
#include <kernel/resource.h>
#include <kernel/vfs.h>
#include <system/system.h>
#include "base.h"
#include "mouse.h"

static struct interface_node
{

    struct system_group base;
    struct base_mouse_interface *interface;
    struct base_device *device;
    struct system_stream data;
    struct system_stream vx;
    struct system_stream vy;

} inode[8];

static struct system_group root;
static struct system_group dev;

static unsigned int data_read(struct system_node *self, unsigned int offset, unsigned int count, void *buffer)
{

    struct interface_node *node = (struct interface_node *)self->parent;

    return node->interface->read_data(node->device, offset, count, buffer);

}

static unsigned int vx_read(struct system_node *self, unsigned int offset, unsigned int count, void *buffer)
{

    struct interface_node *node = (struct interface_node *)self->parent;
    unsigned char num[32];

    return memory_read(buffer, count, num, ascii_write_value(num, 32, node->interface->vx, 10, 0), offset);

}

static unsigned int vy_read(struct system_node *self, unsigned int offset, unsigned int count, void *buffer)
{

    struct interface_node *node = (struct interface_node *)self->parent;
    unsigned char num[32];

    return memory_read(buffer, count, num, ascii_write_value(num, 32, node->interface->vy, 10, 0), offset);

}

static unsigned int find_inode()
{

    unsigned int i;

    for (i = 1; i < 8; i++)
    {

        if (!inode[i].base.node.parent)
            return i;

    }

    return 0;

}

static void init_inode(struct interface_node *node, struct base_mouse_interface *interface, struct base_device *device)
{

    memory_clear(node, sizeof (struct interface_node));
    system_init_group(&node->base, device->module.name);
    system_init_stream(&node->data, "data");
    system_init_stream(&node->vx, "vx");
    system_init_stream(&node->vy, "vy");

    node->interface = interface;
    node->device = device;
    node->data.node.read = data_read;
    node->vx.node.read = vx_read;
    node->vy.node.read = vy_read;

}

void base_mouse_register_interface(struct base_mouse_interface *interface, struct base_device *device)
{

    unsigned int index = find_inode();

    if (!index)
        return;

    init_inode(&inode[index], interface, device);
    system_group_add(&dev, &inode[index].base.node);
    system_group_add(&inode[index].base, &inode[index].data.node);
    system_group_add(&inode[index].base, &inode[index].vx.node);
    system_group_add(&inode[index].base, &inode[index].vy.node);

}

void base_mouse_init_interface(struct base_mouse_interface *interface, unsigned int (*read_data)(struct base_device *device, unsigned int offset, unsigned int count, void *buffer))
{

    memory_clear(interface, sizeof (struct base_mouse_interface));
    base_init_interface(&interface->base, BASE_INTERFACE_TYPE_OTHER);

    interface->read_data = read_data;

}

void base_mouse_setup()
{

    memory_clear(inode, sizeof (struct interface_node) * 8);
    system_init_group(&root, "mouse");
    system_register_node(&root.node);
    system_init_group(&dev, "dev");
    system_group_add(&root, &dev.node);

}


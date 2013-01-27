#define BINARY_FORMAT_SLOTS             4

struct binary_format
{

    unsigned int (*match)(struct vfs_interface *interface, unsigned int id);
    unsigned int (*find_symbol)(struct vfs_interface *interface, unsigned int id, unsigned int count, const char *symbol);
    unsigned int (*copy_program)(struct vfs_interface *interface, unsigned int id);
    unsigned int (*relocate)(struct vfs_interface *interface, unsigned int id, unsigned int address);

};

unsigned int binary_find_symbol(struct vfs_interface *interface, unsigned int id, unsigned int count, const char *symbol);
unsigned int binary_copy_program(struct vfs_interface *interface, unsigned int id);
unsigned int binary_relocate(struct vfs_interface *interface, unsigned int id, unsigned int address);
void binary_register_format(struct binary_format *format);
void binary_unregister_format(struct binary_format *format);
void binary_init_format(struct binary_format *format, unsigned int (*match)(struct vfs_interface *interface, unsigned int id), unsigned int (*find_symbol)(struct vfs_interface *interface, unsigned int id, unsigned int count, const char *symbol), unsigned int (*copy_program)(struct vfs_interface *interface, unsigned int id), unsigned int (*relocate)(struct vfs_interface *interface, unsigned int id, unsigned int address));
void binary_setup();
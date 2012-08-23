#ifndef MODULES_PS2_H
#define MODULES_PS2_H

#define PS2_REGISTER_DATA    0x60
#define PS2_REGISTER_COMMAND 0x64

#define PS2_IRQ_KBD 0x01
#define PS2_IRQ_MOUSE 0x0C

#define PS2_KBD_DEVICE_TYPE   0x3205
#define PS2_KBD_DRIVER_TYPE   0x0005
#define PS2_MOUSE_DEVICE_TYPE 0x4205
#define PS2_MOUSE_DRIVER_TYPE 0x0059

struct ps2_kbd_buffer
{

    char buffer[256];
    unsigned int size;
    unsigned int head;
    unsigned int tail;
    unsigned int (*getc)(struct ps2_kbd_buffer *self, char *buffer);
    unsigned int (*putc)(struct ps2_kbd_buffer *self, char *buffer);

};

struct ps2_kbd_device
{

    struct modules_device base;
    unsigned int irq;

};

struct ps2_kbd_driver
{

    struct modules_driver base;
    struct ps2_kbd_buffer buffer;
    char *map;
    unsigned int escaped;
    unsigned int toggleAlt;
    unsigned int toggleCtrl;
    unsigned int toggleShift;

};

struct ps2_mouse_device
{

    struct modules_device base;
    unsigned int irq;

};

struct ps2_mouse_driver
{

    struct modules_driver base;
    unsigned char cycle;
    char status;
    char x;
    char y;

};

void ps2_kbd_device_init(struct ps2_kbd_device *device, unsigned int irq);
void ps2_kbd_driver_init(struct ps2_kbd_driver *driver);
void ps2_mouse_device_init(struct ps2_mouse_device *device, unsigned int irq);
void ps2_mouse_driver_init(struct ps2_mouse_driver *driver);

#endif


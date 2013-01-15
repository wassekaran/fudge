#include <fudge/kernel.h>
#include "idt.h"

static struct idt_entry entries[IDT_ENTRY_SLOTS];
static struct idt_pointer pointer;

void idt_set_entry(enum idt_index index, void (*callback)(), unsigned short selector, unsigned char flags)
{

    unsigned int base = (unsigned int)callback;

    if (index >= IDT_ENTRY_SLOTS)
        return;

    entries[index].baseLow = (base & 0xFFFF);
    entries[index].baseHigh = (base >> 16);
    entries[index].selector = selector;
    entries[index].flags = flags;

}

struct idt_pointer *idt_setup()
{

    memory_clear(&entries, sizeof (struct idt_entry) * IDT_ENTRY_SLOTS);

    pointer.base = entries;
    pointer.limit = (sizeof (struct idt_entry) * IDT_ENTRY_SLOTS) - 1;

    return &pointer;

}


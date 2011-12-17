#ifndef KERNEL_MMU_H
#define KERNEL_MMU_H

#define MMU_ERROR_PRESENT  1 << 0
#define MMU_ERROR_RW       1 << 1
#define MMU_ERROR_USER     1 << 2
#define MMU_ERROR_RESERVED 1 << 3
#define MMU_ERROR_FETCH    1 << 4

struct mmu_unit
{

    void (*setup)();
    void (*enable)();
    void *(*get_task_memory)(unsigned int id);
    void (*load_task_memory)(void *paddress);
    void (*map_task_memory)(void *paddress, void *vaddress, unsigned int size, unsigned int tflags, unsigned int pflags);

};

extern void mmu_pagefault(unsigned int address, unsigned int flags);
extern void *mmu_get_task_memory(unsigned int id);
extern void mmu_load_task_memory(void *paddress);
extern void mmu_map_task_memory(void *paddress, void *vaddress, unsigned int size, unsigned int tflags, unsigned int pflags);
extern void mmu_unit_init(struct mmu_unit *unit, void (*setup)(), void (*enable)(), void *(*get_task_memory)(unsigned int id), void (*load_task_memory)(void *paddress), void (*map_task_memory)(void *paddress, void *vaddress, unsigned int size, unsigned int tflags, unsigned int pflags));
extern void mmu_register_unit(struct mmu_unit *unit);

#endif


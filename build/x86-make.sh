#!/bin/sh

DIR_KERNEL="../kernel"
DIR_KERNEL_ARCH="../kernel/arch/x86"
DIR_LIB="../lib"
DIR_RAMDISK="../ramdisk"
DIR_TOOLS="../tools"

ASM="nasm"
ASMFLAGS="-f elf"
GCC="gcc"
GCCFLAGS="-c -O2 -I../include -Wall -Wextra -ffreestanding -nostdlib -nostartfiles -nodefaultlibs"
LD="ld"
LDFLAGS=-"T./linker-x86.ld"

$GCC $GCCFLAGS $DIR_KERNEL/assert.c -o $DIR_KERNEL/assert.o
$GCC $GCCFLAGS $DIR_KERNEL/elf.c -o $DIR_KERNEL/elf.o
$GCC $GCCFLAGS $DIR_KERNEL/vfs.c -o $DIR_KERNEL/vfs.o
$GCC $GCCFLAGS $DIR_KERNEL/kernel.c -o $DIR_KERNEL/kernel.o
$GCC $GCCFLAGS $DIR_KERNEL/mboot.c -o $DIR_KERNEL/mboot.o
$GCC $GCCFLAGS $DIR_KERNEL/shell.c -o $DIR_KERNEL/shell.o
$GCC $GCCFLAGS $DIR_KERNEL_ARCH/arch.c -o $DIR_KERNEL_ARCH/arch.o
$GCC $GCCFLAGS $DIR_KERNEL_ARCH/ata.c -o $DIR_KERNEL_ARCH/ata.o
$ASM $ASMFLAGS $DIR_KERNEL_ARCH/cr.s -o $DIR_KERNEL_ARCH/cr.o
$GCC $GCCFLAGS $DIR_KERNEL_ARCH/fpu.c -o $DIR_KERNEL_ARCH/fpu.o
$ASM $ASMFLAGS $DIR_KERNEL_ARCH/fpus.s -o $DIR_KERNEL_ARCH/fpus.o
$GCC $GCCFLAGS $DIR_KERNEL_ARCH/gdt.c -o $DIR_KERNEL_ARCH/gdt.o
$ASM $ASMFLAGS $DIR_KERNEL_ARCH/gdts.s -o $DIR_KERNEL_ARCH/gdts.o
$GCC $GCCFLAGS $DIR_KERNEL_ARCH/idt.c -o $DIR_KERNEL_ARCH/idt.o
$ASM $ASMFLAGS $DIR_KERNEL_ARCH/idts.s -o $DIR_KERNEL_ARCH/idts.o
$ASM $ASMFLAGS $DIR_KERNEL_ARCH/init.s -o $DIR_KERNEL_ARCH/init.o
$ASM $ASMFLAGS $DIR_KERNEL_ARCH/ios.s -o $DIR_KERNEL_ARCH/io.o
$GCC $GCCFLAGS $DIR_KERNEL_ARCH/irq.c -o $DIR_KERNEL_ARCH/irq.o
$ASM $ASMFLAGS $DIR_KERNEL_ARCH/irqs.s -o $DIR_KERNEL_ARCH/irqs.o
$GCC $GCCFLAGS $DIR_KERNEL_ARCH/isr.c -o $DIR_KERNEL_ARCH/isr.o
$ASM $ASMFLAGS $DIR_KERNEL_ARCH/isrs.s -o $DIR_KERNEL_ARCH/isrs.o
$GCC $GCCFLAGS $DIR_KERNEL_ARCH/kbd.c -o $DIR_KERNEL_ARCH/kbd.o
$GCC $GCCFLAGS $DIR_KERNEL_ARCH/mmu.c -o $DIR_KERNEL_ARCH/mmu.o
$GCC $GCCFLAGS $DIR_KERNEL_ARCH/pit.c -o $DIR_KERNEL_ARCH/pit.o
$GCC $GCCFLAGS $DIR_KERNEL_ARCH/rtc.c -o $DIR_KERNEL_ARCH/rtc.o
$GCC $GCCFLAGS $DIR_KERNEL_ARCH/screen.c -o $DIR_KERNEL_ARCH/screen.o
$GCC $GCCFLAGS $DIR_KERNEL_ARCH/syscall.c -o $DIR_KERNEL_ARCH/syscall.o
$GCC $GCCFLAGS $DIR_LIB/call.c -o $DIR_LIB/call.o
$ASM $ASMFLAGS $DIR_LIB/calls.s -o $DIR_LIB/calls.o
$GCC $GCCFLAGS $DIR_LIB/cbuffer.c -o $DIR_LIB/cbuffer.o
$GCC $GCCFLAGS $DIR_LIB/memory.c -o $DIR_LIB/memory.o
$GCC $GCCFLAGS $DIR_LIB/stack.c -o $DIR_LIB/stack.o
$GCC $GCCFLAGS $DIR_LIB/string.c -o $DIR_LIB/string.o
$GCC $GCCFLAGS $DIR_LIB/vfs.c -o $DIR_LIB/vfs.o

$LD $LDFLAGS \
    $DIR_KERNEL/assert.o \
    $DIR_KERNEL/elf.o \
    $DIR_KERNEL/vfs.o \
    $DIR_KERNEL/kernel.o \
    $DIR_KERNEL/mboot.o \
    $DIR_KERNEL/shell.o \
    $DIR_KERNEL_ARCH/arch.o \
    $DIR_KERNEL_ARCH/ata.o \
    $DIR_KERNEL_ARCH/cr.o \
    $DIR_KERNEL_ARCH/fpu.o \
    $DIR_KERNEL_ARCH/fpus.o \
    $DIR_KERNEL_ARCH/gdt.o \
    $DIR_KERNEL_ARCH/gdts.o \
    $DIR_KERNEL_ARCH/idt.o \
    $DIR_KERNEL_ARCH/idts.o \
    $DIR_KERNEL_ARCH/init.o \
    $DIR_KERNEL_ARCH/io.o \
    $DIR_KERNEL_ARCH/irqs.o \
    $DIR_KERNEL_ARCH/isrs.o \
    $DIR_KERNEL_ARCH/irq.o \
    $DIR_KERNEL_ARCH/isr.o \
    $DIR_KERNEL_ARCH/kbd.o \
    $DIR_KERNEL_ARCH/mmu.o \
    $DIR_KERNEL_ARCH/pit.o \
    $DIR_KERNEL_ARCH/rtc.o \
    $DIR_KERNEL_ARCH/screen.o \
    $DIR_KERNEL_ARCH/syscall.o \
    $DIR_LIB/call.o \
    $DIR_LIB/calls.o \
    $DIR_LIB/cbuffer.o \
    $DIR_LIB/memory.o \
    $DIR_LIB/stack.o \
    $DIR_LIB/string.o \
    $DIR_LIB/vfs.o \
    -o root/boot/kernel

ASM="nasm"
ASMFLAGS="-f elf"
GCC="gcc"
GCCFLAGS="-c -O2 -I../include/lib -Wall -ffreestanding -nostdlib -nostartfiles -nodefaultlibs"
LD="ld"
LDFLAGS="-Ttext 0x300000 -e main"

$GCC $GCCFLAGS $DIR_RAMDISK/cat.c -o $DIR_RAMDISK/cat.o
$LD $LDFLAGS $DIR_RAMDISK/cat.o $DIR_LIB/memory.o $DIR_LIB/string.o $DIR_LIB/vfs.o $DIR_LIB/call.o $DIR_LIB/calls.o -o $DIR_RAMDISK/cat

$ASM $ASMFLAGS $DIR_RAMDISK/cpu.s -o $DIR_RAMDISK/cpus.o
$GCC $GCCFLAGS $DIR_RAMDISK/cpu.c -o $DIR_RAMDISK/cpu.o
$LD $LDFLAGS $DIR_RAMDISK/cpu.o $DIR_RAMDISK/cpus.o $DIR_LIB/memory.o $DIR_LIB/string.o $DIR_LIB/vfs.o $DIR_LIB/call.o $DIR_LIB/calls.o -o $DIR_RAMDISK/cpu

$GCC $GCCFLAGS $DIR_RAMDISK/date.c -o $DIR_RAMDISK/date.o
$LD $LDFLAGS $DIR_RAMDISK/date.o $DIR_LIB/memory.o $DIR_LIB/stack.o $DIR_LIB/string.o $DIR_LIB/vfs.o $DIR_LIB/call.o $DIR_LIB/calls.o -o $DIR_RAMDISK/date

$GCC $GCCFLAGS $DIR_RAMDISK/echo.c -o $DIR_RAMDISK/echo.o
$LD $LDFLAGS $DIR_RAMDISK/echo.o $DIR_LIB/memory.o $DIR_LIB/string.o $DIR_LIB/vfs.o $DIR_LIB/call.o $DIR_LIB/calls.o -o $DIR_RAMDISK/echo

$GCC $GCCFLAGS $DIR_RAMDISK/elf.c -o $DIR_RAMDISK/elf.o
$LD $LDFLAGS $DIR_RAMDISK/elf.o $DIR_LIB/memory.o $DIR_LIB/string.o $DIR_LIB/vfs.o $DIR_LIB/call.o $DIR_LIB/calls.o -o $DIR_RAMDISK/elf

$GCC $GCCFLAGS $DIR_RAMDISK/hello.c -o $DIR_RAMDISK/hello.o
$LD $LDFLAGS $DIR_RAMDISK/hello.o $DIR_LIB/memory.o $DIR_LIB/string.o $DIR_LIB/vfs.o $DIR_LIB/call.o $DIR_LIB/calls.o -o $DIR_RAMDISK/hello

$GCC $GCCFLAGS $DIR_RAMDISK/ls.c -o $DIR_RAMDISK/ls.o
$LD $LDFLAGS $DIR_RAMDISK/ls.o $DIR_LIB/memory.o $DIR_LIB/string.o $DIR_LIB/vfs.o $DIR_LIB/call.o $DIR_LIB/calls.o -o $DIR_RAMDISK/ls

$GCC $GCCFLAGS $DIR_RAMDISK/reboot.c -o $DIR_RAMDISK/reboot.o
$LD $LDFLAGS $DIR_RAMDISK/reboot.o $DIR_LIB/memory.o $DIR_LIB/string.o $DIR_LIB/vfs.o $DIR_LIB/call.o $DIR_LIB/calls.o -o $DIR_RAMDISK/reboot

$GCC $GCCFLAGS $DIR_RAMDISK/shell.c -o $DIR_RAMDISK/shell.o
$LD $LDFLAGS $DIR_RAMDISK/shell.o $DIR_LIB/memory.o $DIR_LIB/stack.o $DIR_LIB/string.o $DIR_LIB/vfs.o $DIR_LIB/call.o $DIR_LIB/calls.o -o $DIR_RAMDISK/shell

$GCC $GCCFLAGS $DIR_RAMDISK/timer.c -o $DIR_RAMDISK/timer.o
$LD $LDFLAGS $DIR_RAMDISK/timer.o $DIR_LIB/memory.o $DIR_LIB/string.o $DIR_LIB/vfs.o $DIR_LIB/call.o $DIR_LIB/calls.o -o $DIR_RAMDISK/timer

GCC="gcc"
GCCFLAGS="-O2"

$GCC $GCCFLAGS $DIR_TOOLS/mkinitrd.c -o $DIR_TOOLS/mkinitrd

$DIR_TOOLS/mkinitrd $DIR_RAMDISK/about.txt about.txt $DIR_RAMDISK/cat cat $DIR_RAMDISK/cpu cpu $DIR_RAMDISK/date date $DIR_RAMDISK/echo echo $DIR_RAMDISK/elf elf $DIR_RAMDISK/hello hello $DIR_RAMDISK/help.txt help.txt $DIR_RAMDISK/ls ls $DIR_RAMDISK/reboot reboot $DIR_RAMDISK/shell shell $DIR_RAMDISK/timer timer


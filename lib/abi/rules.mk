L:=\
    $(DIR_LIB)/abi/abi.a \

O:=\
    $(DIR_LIB)/abi/file.o \

include $(DIR_LIB)/abi/$(ARCH)/rules.mk
include $(DIR_MK)/lib.mk

L:=\
    $(DIR_LIB)/abi/qabi.a \

O:=\
    $(DIR_LIB)/abi/file.o \

include $(DIR_LIB)/abi/$(ARCH)/qrules.mk
include $(DIR_MK)/lib.mk

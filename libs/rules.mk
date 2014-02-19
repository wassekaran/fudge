$(LIBS_PATH)/%.o: CFLAGS+=-I$(LIBS_PATH)

include $(LIBS_PATH)/fudge/rules.mk
include $(LIBS_PATH)/kernel/rules.mk
include $(LIBS_PATH)/posix/rules.mk
include $(LIBS_PATH)/cpio/rules.mk
include $(LIBS_PATH)/elf/rules.mk
include $(LIBS_PATH)/tar/rules.mk
include $(LIBS_PATH)/$(ARCH)/arch/rules.mk
include $(LIBS_PATH)/$(ARCH)/abi/rules.mk
include $(LIBS_PATH)/$(ARCH)/$(LOADER)/rules.mk

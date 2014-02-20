$(PACKAGES_PATH)/%.o: CFLAGS+=-I$(LIBS_PATH) -I$(LIBS_PATH)/fudge

USERLIBS:=$(LIBABI) $(LIBFUDGE)

include $(PACKAGES_PATH)/cat/rules.mk
include $(PACKAGES_PATH)/cconv/rules.mk
include $(PACKAGES_PATH)/col/rules.mk
include $(PACKAGES_PATH)/complete/rules.mk
include $(PACKAGES_PATH)/count/rules.mk
include $(PACKAGES_PATH)/cpio/rules.mk
include $(PACKAGES_PATH)/crc/rules.mk
include $(PACKAGES_PATH)/date/rules.mk
include $(PACKAGES_PATH)/dep/rules.mk
include $(PACKAGES_PATH)/dump/rules.mk
include $(PACKAGES_PATH)/echo/rules.mk
include $(PACKAGES_PATH)/head/rules.mk
include $(PACKAGES_PATH)/hello/rules.mk
include $(PACKAGES_PATH)/help/rules.mk
include $(PACKAGES_PATH)/init/rules.mk
include $(PACKAGES_PATH)/keymap/rules.mk
include $(PACKAGES_PATH)/ls/rules.mk
include $(PACKAGES_PATH)/mandelbrot/rules.mk
include $(PACKAGES_PATH)/md5/rules.mk
include $(PACKAGES_PATH)/mod/rules.mk
include $(PACKAGES_PATH)/monitor/rules.mk
include $(PACKAGES_PATH)/motd/rules.mk
include $(PACKAGES_PATH)/mount/rules.mk
include $(PACKAGES_PATH)/name/rules.mk
include $(PACKAGES_PATH)/nl/rules.mk
include $(PACKAGES_PATH)/pcx/rules.mk
include $(PACKAGES_PATH)/reboot/rules.mk
include $(PACKAGES_PATH)/sha1/rules.mk
include $(PACKAGES_PATH)/share/rules.mk
include $(PACKAGES_PATH)/shell/rules.mk
include $(PACKAGES_PATH)/slang/rules.mk
include $(PACKAGES_PATH)/sleep/rules.mk

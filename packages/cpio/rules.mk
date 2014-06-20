BIN:=$(PACKAGES_PATH)/cpio/cpio
OBJ:=$(PACKAGES_PATH)/cpio/cpio.o

$(BIN): $(OBJ) $(LIB_libs/cpio) $(USERLIBS)
	$(LD) $(LDFLAGS) -o $@ $^

PACKAGES+=$(BIN)
PACKAGES_OBJECTS+=$(OBJ)

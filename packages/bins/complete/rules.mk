BIN:=$(PACKAGES_BINS_PATH)/complete/complete
OBJ:=$(PACKAGES_BINS_PATH)/complete/complete.o

$(BIN): $(OBJ) $(USERLIBS)
	$(LD) $(LDFLAGS) -o $@ $^

PACKAGES+=$(BIN)
PACKAGES_OBJECTS+=$(OBJ)

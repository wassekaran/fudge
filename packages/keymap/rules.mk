BIN_$(DIR):=$(DIR)/keymapse
OBJ_$(DIR):=$(DIR)/keymapse.o

$(BIN_$(DIR)): $(OBJ_$(DIR))
	$(LD) -o $@ $^ $(LDFLAGS)

PACKAGES_BUILD:=$(PACKAGES_BUILD) $(BIN_$(DIR))
PACKAGES_CLEAN:=$(PACKAGES_CLEAN) $(BIN_$(DIR)) $(OBJ_$(DIR))

BIN_$(DIR):=$(DIR)/keymapus
OBJ_$(DIR):=$(DIR)/keymapus.o

$(BIN_$(DIR)): $(OBJ_$(DIR))
	$(LD) -o $@ $^ $(LDFLAGS)

PACKAGES_BUILD:=$(PACKAGES_BUILD) $(BIN_$(DIR))
PACKAGES_CLEAN:=$(PACKAGES_CLEAN) $(BIN_$(DIR)) $(OBJ_$(DIR))

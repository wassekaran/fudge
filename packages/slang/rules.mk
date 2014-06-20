BIN_$(DIR):=$(DIR)/slang
OBJ_$(DIR):=$(DIR)/slang.o $(DIR)/parse.o $(DIR)/token.o

$(BIN_$(DIR)): $(OBJ_$(DIR))
	$(LD) -o $@ $^ $(LDFLAGS)

PACKAGES_BUILD:=$(PACKAGES_BUILD) $(BIN_$(DIR))
PACKAGES_CLEAN:=$(PACKAGES_CLEAN) $(BIN_$(DIR)) $(OBJ_$(DIR))

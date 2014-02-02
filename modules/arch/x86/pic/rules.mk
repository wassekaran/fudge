MOD:=$(MODULES_ARCH_PATH)/pic/pic.ko
OBJ:=$(MODULES_ARCH_PATH)/pic/main.o $(MODULES_ARCH_PATH)/pic/pic.o

$(MOD): $(OBJ) $(LIBFUDGE)
	$(LD) $(LDFLAGS) -o $@ $^

MODULES+=$(MOD)
MODULES_OBJECTS+=$(OBJ)

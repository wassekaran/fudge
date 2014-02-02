MOD:=$(MODULES_ARCH_PATH)/smp/smp.ko
OBJ:=$(MODULES_ARCH_PATH)/smp/main.o

$(MOD): $(OBJ) $(LIBFUDGE)
	$(LD) $(LDFLAGS) -o $@ $^

MODULES+=$(MOD)
MODULES_OBJECTS+=$(OBJ)

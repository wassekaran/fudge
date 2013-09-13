MOD:=modules/base/base.ko
OBJ:=modules/base/main.o modules/base/keyboard.o

$(MOD): $(OBJ) $(LIBFUDGE)
	$(LD) $(LDFLAGS) -o $@ $^

MODULES+=$(MOD)
MODULES_OBJECTS+=$(OBJ)

PCXDATA_BIN:=$(PACKAGES_PATH)/pcx/pcxdata
PCXDATA_OBJ:=$(PACKAGES_PATH)/pcx/pcxdata.o
PCXCMAP_BIN:=$(PACKAGES_PATH)/pcx/pcxcmap
PCXCMAP_OBJ:=$(PACKAGES_PATH)/pcx/pcxcmap.o

$(PCXDATA_BIN): $(PCXDATA_OBJ) $(LIB_libs/gfx) $(USERLIBS)
	$(LD) $(LDFLAGS) -o $@ $^

$(PCXCMAP_BIN): $(PCXCMAP_OBJ) $(LIB_libs/gfx) $(USERLIBS)
	$(LD) $(LDFLAGS) -o $@ $^

PACKAGES+=$(PCXDATA_BIN) $(PCXCMAP_BIN)
PACKAGES_OBJECTS+=$(PCXDATA_OBJ) $(PCXCMAP_OBJ)

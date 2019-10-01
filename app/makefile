include ../config

INCLUDE=-I. -I../include -I$(PREFIX)/include
LIB=-L../lib -L$(PREFIX)/lib
BINDIR=$(PREFIX)/bin

LINK=-lliw `zeda-config -l`

ifeq ($(CONFIG_USE_LIBDL),y)
	LINK += "-ldl"
endif

ifeq ($(CONFIG_USE_PTHREAD),y)
	LINK += "-lpthread"
endif

ifeq ($(CONFIG_USE_RT),y)
	LINK += "-lrt"
endif

INSTALL=install -m 755
UNINSTALL=rm -f

CONFIGGEN=zeda-config-gen
CONFIG=liw-config
TARGET=$(CONFIG)

#####################################################################
all: $(TARGET)

$(CONFIG):
	@echo " GENERATE" $@
	-@rm -f $@
	@$(CONFIGGEN) -I $(PREFIX)/include -L $(PREFIX)/lib -l "$(LINK)" -v $(VERSION) > $@
install: $(TARGET)
	@echo " INSTALL	" $^
	@$(INSTALL) $^ $(BINDIR)
clean:
	@echo " CLEAN"
	-@rm -f *.o *~ core $(TARGET)
uninstall:
	@echo " UNINSTALL	" $(TARGET)
	@cd $(BINDIR); $(UNINSTALL) $(TARGET); cd -

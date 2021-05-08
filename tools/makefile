include ../config

BINDIR=$(PREFIX)/bin

INSTALL=install -m 755
UNINSTALL=rm -f

INCLUDE=`zeda-config -I`
LIB=`zeda-config -L`
DEF=`zeda-config -D`

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

CONFIGGEN=zeda-config-gen
CONFIG=liw-config

#####################################################################
all: $(CONFIG)

$(CONFIG):
	@echo " GENERATE	" $@
	-@rm -f $@
	@$(CONFIGGEN) -I "$(INCLUDE)" -L "$(LIB)" -D "$(DEF)" -l "$(LINK)" -v $(VERSION) > $@
install: $(CONFIG)
	@echo " INSTALL	" $^
	@$(INSTALL) $^ $(BINDIR)
clean:
	@echo " CLEAN"
	-@rm -f *.o *~ core $(CONFIG)
uninstall:
	@echo " UNINSTALL	" $(CONFIG)
	@$(UNINSTALL) $(BINDIR)/$(CONFIG)

MAKEFILEGEN=`which zeda-makefile-gen`

all:
	@$(MAKEFILEGEN) lib | make -f -
%.o: %.c
	@$(MAKEFILEGEN) lib | make -f - $@
clean:
	@$(MAKEFILEGEN) lib | make -f - clean

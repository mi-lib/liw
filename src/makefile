include ../config

ROOTDIR=..
LIBDIR=$(ROOTDIR)/lib
INCLUDE=-I$(ROOTDIR)/include -I$(PREFIX)/include

CC=gcc
CFLAGS=-Wall -fPIC -O3 $(INCLUDE) -funroll-loops
LD=gcc
LDFLAGS=-shared
SIGNUP=echo "LIW ver."$(VERSION)" Copyright (C) 2000 Tomomichi Sugihara (Zhidao)" >>

OBJ=liw_time.o liw_coproc.o liw_paction.o\
	liw_fifo.o liw_ipc.o liw_lock.o\
	liw_socket.o

ifeq ($(CONFIG_USE_LIBDL),y)
	OBJ += liw_dl.o
endif

ifeq ($(CONFIG_USE_RTC),y)
	OBJ += liw_rtc.o
endif

DLIB=libliw.so

TARGET=$(DLIB)

all: $(TARGET)

$(DLIB): $(OBJ)
	@echo " LD	" $?
	@$(LD) $(LDFLAGS) -o $@ $? > /dev/null; $(SIGNUP) $@
	-@mv $@ $(LIBDIR)
%.o: %.c
	@echo " CC	" $<
	@$(CC) $(CFLAGS) -c $< > /dev/null
clean:
	@echo " CLEAN"
	-@rm -f *.o *~ $(TARGET)

include ../../../config

INCLUDE=-I../../include -I$(PREFIX)/include
LIB=-L../../lib -L$(PREFIX)/lib

CC=gcc
CFLAGS=-Wall -O3 -fPIC $(INCLUDE) $(LIB)

LD=gcc
LFLAGS=-shared

.SUFFIXES: .plg

PLUGIN=plugin1.plg plugin2.plg
TARGET=$(PLUGIN)

all: $(TARGET)

.c.o:
	$(CC) $(CFLAGS) -c $< $(LINK)
.o.plg:
	$(LD) $(LFLAGS) -o $@ $<
clean:
	rm -f *.o *~ $(TARGET)

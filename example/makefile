include ../../config

INCLUDE=`liw-config -I`
LIB=`liw-config -L`
LINK=`liw-config -l`

CC=gcc
CFLAGS=-Wall -O2 $(INCLUDE) $(LIB)

all: $(TARGET)
%: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LINK)
clean :
	rm -f *.o *~ core $(TARGET)

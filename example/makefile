INCLUDE=`liw-config -I`
LIB=`liw-config -L`
LINK=`liw-config -l`

CC=gcc
CFLAGS=-Wall -O2 $(INCLUDE) $(LIB)

TARGET=$(shell ls *.c | xargs -i basename {} .c | tr -s "\n" " ")

all: $(TARGET)
%: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LINK)
clean :
	rm -f *.o *~ core $(TARGET)
	if [ -d plugin ]; then cd plugin; make clean; cd -; fi

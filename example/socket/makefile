TARGET=unserver unclient\
	inetserver inetclient\
	inetserver_pl inetclient_pl

include ../makefile

SOCKNAME=socket_un
CFLAGS+=-DSOCKET_UN_NAME=\"$(SOCKNAME)\"
LINK+=-lpthread

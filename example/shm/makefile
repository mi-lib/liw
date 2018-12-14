TARGET=shmserver shmclient

include ../makefile

shmserver: shmserver.c
	$(CC) $(CFLAGS) -o $@ $? $(LINK)
shmclient: shmclient.c
	$(CC) $(CFLAGS) -o $@ $? $(LINK)

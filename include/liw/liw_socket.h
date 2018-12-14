/* LIW - Linux Wizard
 * Copyright (C) 2000 Tomomichi Sugihara (Zhidao)
 */
/*! \file liw_socket.h
 * \brief socket communication.
 * \author Zhidao
 */

#ifndef __LIW_SOCKET_H__
#define __LIW_SOCKET_H__

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <zeda/zeda.h>

__BEGIN_DECLS

#define LIW_SOCKET_DEFAULT_PROTOCOL 0

typedef struct sockaddr    liwSockAddr;
typedef struct sockaddr_un liwSockAddrUN;
typedef struct sockaddr_in liwSockAddrINET;

/* sockets on UNIX filesystem */

int liwSocketUNOpen(char *name, int type, liwSockAddrUN *addr);
int liwSocketUNBind(char *name, int type, int num);
int liwSocketUNConnect(char *name, int type);
int liwSocketUNAccept(int fd);

/* socket on internet system */

int liwSocketINETOpen(char *ip, int port, int type, liwSockAddrINET *addr);
int liwSocketINETBind(char *ip, int port, int type, int num);
int liwSocketINETConnect(char *ip, int port, int type);
int liwSocketINETAccept(int fd);

__END_DECLS

#endif /* __LIW_SOCKET_H__ */

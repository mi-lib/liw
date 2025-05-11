#include <stdlib.h>
#include <liw/liw_socket.h>
#include <signal.h>

int sfd;

void terminate(int sig)
{
  close( sfd );
  unlink( SOCKET_UN_NAME );
  exit( 1 );
}

int main(void)
{
  int cfd;
  char buf[BUFSIZ];
  int i;

  signal( SIGINT, terminate );
  for( i=0; i<BUFSIZ; i++ ) buf[i] = '\0';
  unlink( SOCKET_UN_NAME );
  sfd = liwSocketUNBind( SOCKET_UN_NAME, SOCK_STREAM, 5 );
  while( 1 ){
    printf( "server is waiting...\n" );
    cfd = liwSocketUNAccept( sfd );
    if( read( cfd, buf, BUFSIZ ) == 0 );
    printf( "read string : %s\n", buf );
    for( i=0; buf[i]; i++ ) buf[i]++;
    if( write( cfd, buf, BUFSIZ ) == 0 );
    close( cfd );
    if( !strncmp( buf, "ibmu", 4 ) ) break;
  }
  close( sfd );
  unlink( SOCKET_UN_NAME );
  return 0;
}

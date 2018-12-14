#include <liw/liw_socket.h>
#include <stdlib.h>
#include <signal.h>

int sfd;

int main(void)
{
  int cfd;
  char buf[BUFSIZ];
  register int i;

  memset( buf, 0, BUFSIZ );
  if( !( sfd = liwSocketINETBind( "127.0.0.1", 3000, SOCK_STREAM, 5 ) ) )
    return 1;

  while( 1 ){
    printf( "server is waiting...\n" );
    if( !( cfd = liwSocketINETAccept( sfd ) ) ) exit( 1 );
    if( read( cfd, buf, BUFSIZ ) == 0 );
    printf( "read string : %s\n", buf );
    for( i=0; buf[i]; i++ ) buf[i]++;
    if( write( cfd, buf, BUFSIZ ) == -1 )
      printf( "cannot send buffer.\n" );
    if( !strncmp( buf, "ibmu", 4 ) ) break;
    close( cfd );
  }
  close( sfd );
  return 0;
}

#include <liw/liw_socket.h>

int main(void)
{
  int fd;
  char buf[BUFSIZ];
  int i;

  for( i=0; i<BUFSIZ; i++ ) buf[i] = '\0';
  fd = liwSocketUNConnect( SOCKET_UN_NAME, SOCK_STREAM );
  if( fd == 0 ){
    perror( "ouch!: client" );
    exit( 1 );
  }
  printf( "enter string: " );
  if( !fgets( buf, BUFSIZ, stdin ) );
  zCutNL( buf );
  if( write( fd, buf, BUFSIZ ) == 0 );
  if( read( fd, buf, BUFSIZ ) == 0 );
  printf( "returned string = %s\n", buf );
  close( fd );
  return 0;
}

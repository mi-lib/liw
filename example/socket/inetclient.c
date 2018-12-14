#include <liw/liw_socket.h>

int main(void)
{
  int fd;
  char buf[BUFSIZ];

  memset( buf, 0, BUFSIZ );
  if( !( fd = liwSocketINETConnect( "127.0.0.1", 3000, SOCK_STREAM ) ) )
    exit( 1 );

  printf( "enter string: " );
  if( !fgets( buf, BUFSIZ, stdin ) );
  zCutNL( buf );
  if( write( fd, buf, BUFSIZ ) == 0 );
  if( read( fd, buf, BUFSIZ ) == 0 );
  printf( "returned string = %s\n", buf );
  close( fd );
  return 0;
}

/* FIFO test - receiver process */

#include <liw/liw_fifo.h>

#define FIFONAME "./fifo_test"

static char buffer[BUFSIZ];

int main(void)
{
  int fd;

  printf( "FIFO receiver started.\n" );
  fd = liwFIFOReadOpen( FIFONAME );

  strcpy( buffer, "waiting..." );

  do{
    if( liwFIFORead( fd, buffer, BUFSIZ ) == LIW_FIFO_INVALID )
      break;
    printf( "%s\n", buffer );
  } while( strcmp( buffer, "halt" ) );

  liwFIFOClose( fd );
  printf( "FIFO receiver terminated.\n" );
  if( liwFIFODestroy( FIFONAME ) == 0 )
    printf( "FIFO has been destroyed.\n" );

  return 0;
}

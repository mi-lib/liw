/* FIFO test - sender process */

#include <liw/liw_fifo.h>
#include <liw/liw_lock.h>

#define FIFONAME "./fifo_test"
#define LOCK "./.fifo_test_lock"

int main(void)
{
  int fd;
  char command[BUFSIZ];

  /* initialize */
  printf( "FIFO sender started.\n" );
  liwLockInit( LOCK );
  while( liwLock( getpid() ) == false );
  fd = liwFIFOWriteOpen( FIFONAME );

  memset( command, 0, BUFSIZ );
  do{
    printf( "enter: " );
    if( !fgets( command, BUFSIZ, stdin ) );
    command[strlen(command)-1] = '\0';
    liwFIFOWrite( fd, command, BUFSIZ );
  } while( strcmp( command, "quit" ) && strcmp( command, "halt" ) );

  /* terminate */
  liwFIFOClose( fd );
  printf( "FIFO sender terminated.\n" );
  liwUnlock( getpid() );

  return 1;
}

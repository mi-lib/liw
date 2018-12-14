/* shared memory test - server process */

#include <liw/liw_ipc.h>

#define ZSHMKEY "./shmserver.c"

static liwSHM shm;

void zshmterminate(int sig)
{
  /* remove shared memory */
  if( !liwSHMDestroy( &shm ) ) exit(1);
  printf( "shared memory removed.\n" );
}

void signalon(void)
{
  signal( SIGABRT, zshmterminate );
  signal( SIGHUP,  zshmterminate );
  signal( SIGINT,  zshmterminate );
  signal( SIGQUIT, zshmterminate );
  signal( SIGILL,  zshmterminate );
}

int main(void)
{
  /* get shared memory ID and attach shared memory. */
  if( liwSHMAlloc( &shm, ZSHMKEY, BUFSIZ ) < 0 )
    exit(1);

  signalon();

  printf( "get shared memory ID:%d\n", shm.id );
  printf( "memory attached to %p.\n", shm.mp );

  /* loop */
  while( 1 ){
    printf( "string:%s\n", (char *)shm.mp );
    if( !strcmp( (char *)shm.mp, "halt" ) ) break;
  }

  /* detach shared memory */
  if( !liwSHMDetach( &shm ) ) exit(1);
  printf( "shared memory detached.\n" );

  /* process termination */
  zshmterminate( 0 );
  return 0;
}

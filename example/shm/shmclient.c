/* shared memory test - client process */

#include <liw/liw_ipc.h>

#define ZSHMKEY "./shmserver.c"

int main(void)
{
  liwSHM shm;
  char *shbuf, text[BUFSIZ];

  /* get shared memory ID and attach shared memory flagp. */
  if( liwSHMAttach( &shm, ZSHMKEY, BUFSIZ ) < 0 )
    exit(1);
  printf( "get shared memory ID:%d\n", shm.id );
  printf( "memory attached to %p.\n", shm.mp );
  shbuf = (char *)shm.mp;
  shbuf[0] = '\0';

  printf( "to terminate the client, enter 'quit'.\n" );
  printf( "to terminate both the client and the server, enter 'halt'.\n" );
  /* loop */
  while( 1 ){
    printf( "enter a string:" );
    if( !fgets( text, BUFSIZ, stdin ) );
    text[strlen(text)-1] = '\0';
    strcpy( shbuf, text );
    printf( "text is set for :%s\n", text );
    if( !strcmp( text, "quit" ) || !strcmp( text, "halt" ) ) break;
  }

  /* detach shared memory */
  /* process termination */
  liwSHMDetach( &shm );
  printf( "shared memory detached.\n" );
  return 0;
}

#include <liw/liw_ipc.h>

int main(int argc, char *argv[])
{
  int i;
  char c = 'O';
  int id;

  srand( (unsigned int)getpid() );
  id = liwSEMGet( "./semtest.c" );
  if( argc > 1 ) c = argv[1][0];

  if( !liwSEMCreate( id ) ) exit( 1 );
  sleep( 2 );

  for( i=0; i<10; i++ ){
    if( !liwSEMPasseren( id ) ) exit( 1 );
    printf( "%c", c ); fflush( stdout );
    sleep( rand() % 3 ); /* random wait */
    printf( "%c", c ); fflush( stdout );
    if( !liwSEMVrijgeven( id ) ) exit( 1 );
    sleep( rand() % 2 ); /* random wait */
  }
  printf( "\n%d - finished.\n", getpid() );

  /* liwSEMDestroy( id ); */
  return 0;
}

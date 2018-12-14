#include <liw/liw_paction.h>

void ding(int sig)
{
  static unsigned long msec_cnt = 0;

  msec_cnt++;
  if( !( msec_cnt % 100 ) ){
    printf( "%s:%lu [ms]\n", __FUNCTION__, msec_cnt/10 );
  }
}

int main(void)
{
  liwPAction pa;
  int i;

  liwPActionCreate( &pa, 10000, ding );
  /* set intarval timer (1ms) */
  if( liwPActionStart( &pa ) < 0 ) exit( 1 );
  /* loop */
  for( i=0; i<10; i++ ){
    liwSleep( 1, 0 ); /* sleep 1 sec */
    printf( "[%02d] yeah-!\n", i );
  }
  printf( "stop.\n" );
  if( liwPActionStop( &pa ) < 0 ) exit( 1 );
  liwSleep( 3, 0 );
  if( liwPActionStart( &pa ) < 0 ) exit( 1 );
  printf( "restart.\n" );
  for( i=0; i<10; i++ ){
    liwSleep( 1, 0 ); /* sleep 1 sec */
    printf( "[%02d] yeah-!\n", i );
  }
  liwPActionStop( &pa );
  liwPActionDestroy( &pa );
  return 0;
}

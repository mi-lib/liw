#include <liw/liw_paction.h>

void ding(int signum, siginfo_t *info, void *ctxt)
{
  static unsigned long msec_cnt = 0;

  msec_cnt++;
  if( !( msec_cnt % 100 ) ){
    printf( "%s:%lu sec\n", __FUNCTION__, msec_cnt / 100 );
  }
  return;
}

void dong(int signum, siginfo_t *info, void *ctxt)
{
  static unsigned long msec_cnt = 0;

  msec_cnt++;
  if( !( msec_cnt % 100 ) ){
    printf( "%s:%lu sec\n", __FUNCTION__, msec_cnt / 100 );
  }
  return;
}

int main(void)
{
  liwPActionRT pa1, pa2;
  int i;

  liwPActionRTCreate( &pa1, 1, 10000000, ding );
  liwPActionRTCreate( &pa2, 2, 20000000, dong );
  /* loop */
  liwPActionRTStart( &pa1 );
  for( i=0; i<10; i++ ){
    liwSleep( 1, 0 );
    /* sleep 1 sec */
  }
  liwPActionRTStop( &pa1 );
  liwSleep( 3, 0 );
  liwPActionRTStart( &pa1 );
  liwPActionRTStart( &pa2 );
  for( i=0; i<10; i++ ){
    liwSleep( 1, 0 );
    /* sleep 1 sec */
  }
  liwPActionRTStop( &pa1 );
  liwPActionRTStop( &pa2 );
  return 0;
}

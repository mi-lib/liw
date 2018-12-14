#include <liw/liw_rtc.h>

int main(void)
{
  int i, fd;

  fd = liwRTCOpen();

  /* Turn on update interrupts (one per second) */
  liwRTCUpdateInterruptsOn( fd );
  eprintf( "Counting 5 update (1/sec) interrupts from reading /dev/rtc:" );
  for( i=1; i<6; i++ ){
    /* This read will block */
    liwRTCRead( fd );
    eprintf( " %d", i );
  }
  eprintf( "\nAgain, from using select(2) on /dev/rtc:" );
  for( i=1; i<6; i++ ){
    liwRTCSetSelect( fd, 5 );
    /* This read won't block unlike the select-less case above. */
    liwRTCRead( fd );
    eprintf( " %d", i );
  }
  eprintf( "\n" );
  /* Turn off update interrupts */
  liwRTCUpdateInterruptsOff( fd );

  liwRTCClose( fd );
  return 0;
}

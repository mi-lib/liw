#include <liw/liw_rtc.h>

int main(void)
{
  int i, fd;
  unsigned long tmp;

  fd = liwRTCOpen();

  /* Read periodic IRQ rate */
  liwRTCGetPeriodicIRQ( fd, &tmp );
  eprintf( "\nPeriodic IRQ rate was %ldHz.\n", tmp );

  eprintf( "Counting 20 interrupts at:" );
  /* The frequencies 128Hz, 256Hz, ... 8192Hz are only allowed for root. */
  for( tmp=2; tmp<=64; tmp*=2 ){
    liwRTCSetPeriodicIRQ( fd, tmp );
    eprintf( "\n%ldHz:\t", tmp );
    /* Enable periodic interrupts */
    liwRTCPeriodicIRQOn( fd );
    for( i=1; i<21; i++ ){ /* This blocks */
      liwRTCRead( fd );
      eprintf( " %d", i );
    }
    /* Disable periodic interrupts */
    liwRTCPeriodicIRQOff( fd );
  }
  eprintf( "\n" );

  liwRTCClose( fd );
  return 0;
}

/* realtime 10ms loop test */

#include <liw/liw_rtc.h>
#include <liw/liw_paction.h>

int main(void)
{
  int i, fd;
  unsigned long tmp, now;
  unsigned int val[20];

  fd = liwRTCOpen();

  /* Read periodic IRQ rate */
  liwRTCSetPeriodicIRQ( fd, 1024 );
  liwRTCGetPeriodicIRQ( fd, &tmp );
  eprintf( "Counting 20 interrupts at Periodic IRQ rate %ldHz.\n", tmp );
  /* The frequencies 128Hz, 256Hz, ... 8192Hz are only allowed for root. */

  /* Enable periodic interrupts */
  liwRTCPeriodicIRQOn( fd );
  tmp = liwNow();
  for( i=0; i<20; i++ ){
    /* This blocks */
    liwRTCRead( fd );
    now = liwNow();
    val[i] = now - tmp;
    tmp = now;
  }
  /* Disable periodic interrupts */
  liwRTCPeriodicIRQOff( fd );
  liwRTCClose(fd);

  for( i=0; i<20; tmp = liwNow(), i++ )
    eprintf( " %d: %u\n", i, val[i] );
  return 0;
}

/* this program is to confirm that thread use on RTC is prohibited,
 * and thus, does not run without errors.
 */

#include <liw/liw_rtc.h>
#include <liw/liw_paction.h>
#include <pthread.h>

#define TIME 1000

void loop(int hz)
{
  int i, fd;
  unsigned long tmp;

  fd = liwRTCOpen();

  /* Read periodic IRQ rate */
  liwRTCSetPeriodicIRQ( fd, hz );
  liwRTCGetPeriodicIRQ( fd, &tmp );
  eprintf( "Counting 20 interrupts at Periodic IRQ rate %ldHz.\n", tmp );
  /* The frequencies 128Hz, 256Hz, ... 8192Hz are only allowed for root. */

  /* Enable periodic interrupts */
  liwRTCPeriodicIRQOn( fd );
  tmp = liwNow();
  for( i=1; i<TIME; tmp=liwNow(), i++ ){
    /* This blocks */
    liwRTCRead( fd );
    printf( " %d: %d: %lld\n", hz, i, liwNow()-tmp );
  }
  /* Disable periodic interrupts */
  liwRTCPeriodicIRQOff( fd );
  liwRTCClose(fd);
}

int main(int argc, char *argv[])
{
  int i, n;
  pthread_t thread[2];

  n = argc > 1 ? atoi(argv[1]) : 1;
  for( i=1; i<=n; i++ )
    pthread_create( &thread[i-1], NULL, (void *)loop, (void *)(1024/i) );
  for( i=1; i<=n; i++ )
    pthread_join( thread[i-1], NULL );
  return 0;
}

#include <liw/liw_rtc.h>

int main(void)
{
  int fd;
  struct rtc_time rtc_tm;

  fd = liwRTCOpen();

  /* Read the RTC time/date */
  liwRTCGetCurrentTime( fd, &rtc_tm );
  eprintf( "\n\nCurrent RTC date/time is %d-%d-%d, %02d:%02d:%02d.\n",
    rtc_tm.tm_mday, rtc_tm.tm_mon + 1, rtc_tm.tm_year + 1900,
    rtc_tm.tm_hour, rtc_tm.tm_min, rtc_tm.tm_sec );

  /* Set the alarm to 5 sec in the future, and check for rollover */
  liwRTCTMAddSec( &rtc_tm, 5 );
  liwRTCSetAlarm( fd, &rtc_tm );
  /* Read the current alarm settings */
  liwRTCGetAlarm( fd, &rtc_tm );
  eprintf( "Alarm time now set to %02d:%02d:%02d.\n",
    rtc_tm.tm_hour, rtc_tm.tm_min, rtc_tm.tm_sec );

  /* Enable alarm interrupts */
  liwRTCAlarmOn( fd );
  eprintf( "Waiting 5 seconds for alarm..." );
  /* This blocks until the alarm ring causes an interrupt */
  liwRTCRead( fd );
  eprintf( " okay. Alarm rang.\n" );
  /* Disable alarm interrupts */
  liwRTCAlarmOff( fd );

  liwRTCClose( fd );
  return 0;
}

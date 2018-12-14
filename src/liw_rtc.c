/* LIW - Linux Wizard
 * Copyright (C) 2000 Tomomichi Sugihara (Zhidao)
 *
 * liw_rtc - realtime clock driver
 */

#include <liw/liw_rtc.h>

#define LIW_RTC_DEV "/dev/rtc"

int liwRTCOpen(void)
{
  int fd;

  liwAssert( LIW_RTC_DEV, ( fd = open ( LIW_RTC_DEV, O_RDONLY) ) );
  return fd;
}

void liwRTCRead(int fd)
{
  static ulong dummy;

  _liwRTCRead( fd, &dummy );
}

void liwRTCSetSelect(int fd, long timeout)
{
  struct timeval tv;
  fd_set readfds;

  tv.tv_sec = timeout; /* timeout second on select */
  FD_ZERO( &readfds );
  FD_SET( fd, &readfds );
  /* select will wait until an RTC interrupt happens. */
  liwAssert( "select", select( FD_SETSIZE, &readfds, NULL, NULL, &tv ) );
}

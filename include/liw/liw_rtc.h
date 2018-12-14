/* LIW - Linux Wizard
 * Copyright (C) 2000 Tomomichi Sugihara (Zhidao)
 */
/*! \file liw_rtc.h
 * \brief realtime clock driver.
 * \author Zhidao
 */

#ifndef __LIW_RTC_H__
#define __LIW_RTC_H__

#include <linux/rtc.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include <zeda/zeda.h>

#include <liw/liw_debug.h>

int liwRTCOpen(void);
#define liwRTCClose(fd) close((fd))

/* update interrupts */
#define liwRTCUpdateInterruptsOn(fd) \
  liwAssert( "ioctl", ioctl( (fd), RTC_UIE_ON, 0 ) )
#define liwRTCUpdateInterruptsOff(fd) \
  liwAssert( "ioctl", ioctl( (fd), RTC_UIE_OFF, 0 ) )

/* alarm using rtc_tm */
#define liwRTCGetCurrentTime(fd,tm) \
  liwAssert( "ioctl", ioctl( (fd), RTC_RD_TIME, (tm) ) )
#define liwRTCSetAlarm(fd,tm) \
  liwAssert( "ioctl", ioctl( (fd), RTC_ALM_SET, (tm) ) )
#define liwRTCGetAlarm(fd,tm) \
  liwAssert( "ioctl", ioctl( (fd), RTC_ALM_READ, (tm) ) )
#define liwRTCAlarmOn(fd) \
  liwAssert( "ioctl", ioctl( (fd), RTC_AIE_ON, 0 ) )
#define liwRTCAlarmOff(fd) \
  liwAssert( "ioctl", ioctl( (fd), RTC_AIE_OFF, 0 ) )

#define liwRTCTMAlignHour(tm) do{\
  if( (tm)->tm_hour >= 24 ) (tm)->tm_hour %= 24; } while(0)
#define liwRTCTMAlignMin(tm) do{\
  if( (tm)->tm_min >= 60 ){\
    (tm)->tm_min %= 60;\
    (tm)->tm_hour++;\
  }\
  liwRTCTMAlignHour( tm );\
} while(0)
#define liwRTCTMAddMin(tm,min) do{\
  (tm)->tm_min += (min);\
  liwRTCTMAlignMin(tm);\
} while(0)
#define liwRTCTMAlignSec(tm) do{\
  if( (tm)->tm_sec >= 60 ){\
    (tm)->tm_sec %= 60;\
    (tm)->tm_min++;\
  }\
  liwRTCTMAlignMin( tm );\
} while(0)
#define liwRTCTMAddSec(tm,sec) do{\
  (tm)->tm_sec += (sec);\
  liwRTCTMAlignSec(tm);\
} while(0)

/* periodic IRQ */
#define liwRTCGetPeriodicIRQ(fd,hz) \
  liwAssert( "ioctl", ioctl( (fd), RTC_IRQP_READ, (hz) ) )
#define liwRTCSetPeriodicIRQ(fd,hz) \
  liwAssert( "ioctl", ioctl( (fd), RTC_IRQP_SET, (hz) ) )
#define liwRTCPeriodicIRQOn(fd) \
  liwAssert( "ioctl", ioctl( (fd), RTC_PIE_ON, 0 ) )
#define liwRTCPeriodicIRQOff(fd) \
  liwAssert( "ioctl", ioctl( (fd), RTC_PIE_OFF, 0 ) )

/* read RTC */
#define _liwRTCRead(fd,dat) \
  liwAssert( "read", read( (fd), (dat), sizeof(unsigned long) ) )
void liwRTCRead(int fd);

void liwRTCSetSelect(int fd, long timeout);

#endif /* __LIW_RTC_H__ */

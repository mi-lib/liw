/* LIW - Linux Wizard
 * Copyright (C) 2000 Tomomichi Sugihara (Zhidao)
 *
 * liw_paction - timer-managed periodic action
 */

#include <liw/liw_paction.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <errno.h>

/* ********************************************************** */
/* CLASS: liwPAction
 * periodic action
 * ********************************************************** */

static void _liwSetInterval(struct itimerval *iv, long int interval);

void _liwSetInterval(struct itimerval *iv, long int interval)
{
  iv->it_value.tv_sec = 0;
  iv->it_value.tv_usec = interval;
  iv->it_interval.tv_sec = 0;
  iv->it_interval.tv_usec = interval;
}

int liwPActionCreate(liwPAction *pa, long int interval, void (* handler)(int))
{
  memset( &pa->sa, 0, sizeof(struct sigaction) );
  /* set signal handler */
  pa->sa.sa_handler = handler;
  pa->sa.sa_flags = SA_RESTART;
  sigemptyset( &pa->sa.sa_mask );
  if( sigaction( SIGALRM, &pa->sa, NULL ) < 0 ){
    ZRUNERROR( "invalid signal handler assigned" );
    return -1;
  }
  _liwSetInterval( &pa->timer, interval );
  pa->is_running = false;
  return 0;
}

void liwPActionDestroy(liwPAction *pa)
{
  liwPActionCreate( pa, 0, NULL );
  signal( SIGALRM, SIG_DFL );
}

int liwPActionStart(liwPAction *pa)
{
  if( setitimer( ITIMER_REAL, &pa->timer, NULL ) < 0 ){
    ZRUNERROR( "invalid interval specified." );
    return -1;
  }
  pa->is_running = true;
  return 0;
}

int liwPActionStop(liwPAction *pa)
{
  struct itimerval iv;

  _liwSetInterval( &iv, 0 );
  if( setitimer( ITIMER_REAL, &iv, NULL ) < 0 ){
    ZRUNERROR( "invalid interval specified." );
    return -1;
  }
  pa->is_running = false;
  return 0;
}

/* ********************************************************** */
/* CLASS: liwPActionRT
 * POSIX periodic action
 * ********************************************************** */

static void _liwSetIntervalRT(struct itimerspec *is, long int interval);

void _liwSetIntervalRT(struct itimerspec *is, long int interval)
{
  is->it_interval.tv_sec = 0;
  is->it_interval.tv_nsec = interval;
  is->it_value.tv_sec = 0;
  is->it_value.tv_nsec = interval;
}

int liwPActionRTCreate(liwPActionRT *pa, int id, long int interval, void (* handler)(int,siginfo_t*,void*))
{
  memset( &pa->sa, 0, sizeof(struct sigaction) );
  memset( &pa->se, 0, sizeof(struct sigevent) );
  pa->sa.sa_sigaction = handler;
  pa->sa.sa_flags = SA_SIGINFO | SA_RESTART;
  sigemptyset( &pa->sa.sa_mask );
  if( sigaction( SIGRTMIN + id, &pa->sa, NULL ) < 0 ){
    ZRUNERROR( "invalid interval specified." );
    return -1;
  }
  pa->se.sigev_notify = SIGEV_SIGNAL;
  pa->se.sigev_signo = SIGRTMIN + id;
  if( timer_create( CLOCK_REALTIME, &pa->se, (timer_t)&pa->id ) < 0 ){
    ZRUNERROR( "cannot create timer." );
    return -1;
  }
  _liwSetIntervalRT( &pa->is, interval );
  pa->is_running = false;
  return 0;
}

int liwPActionRTStart(liwPActionRT *pa)
{
  if( timer_settime( (timer_t)pa->id, 0, &pa->is, NULL ) < 0 ){
    ZRUNERROR( "cannot set timer." );
    return -1;
  }
  pa->is_running = true;
  return 0;
}

int liwPActionRTStop(liwPActionRT *pa)
{
  struct itimerspec is;

  _liwSetIntervalRT( &is, 0 );
  if( timer_settime( (timer_t)pa->id, 0, &is, NULL ) < 0 ){
    ZRUNERROR( "cannot set timer." );
    return -1;
  }
  pa->is_running = false;
  return 0;
}

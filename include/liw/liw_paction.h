/* LIW - Linux Wizard
 * Copyright (C) 2000 Tomomichi Sugihara (Zhidao)
 */
/*! \file liw_paction.h
 * \brief timer-managed periodic action.
 * \author Zhidao
 */

#ifndef __LIW_PACTION_H__
#define __LIW_PACTION_H__

#include <unistd.h>
#include <signal.h>
#include <liw/liw_time.h>

__BEGIN_DECLS

/* ********************************************************** */
/* CLASS: liwPAction
 * periodic action
 * ********************************************************** */

typedef struct{
  struct sigaction sa;
  struct itimerval timer;
  bool is_running;
} liwPAction;

int liwPActionCreate(liwPAction *pa, long int interval, void (* handler)(int));
void liwPActionDestroy(liwPAction *pa);
int liwPActionStart(liwPAction *pa);
int liwPActionStop(liwPAction *pa);

/* ********************************************************** */
/* CLASS: liwPActionRT
 * POSIX periodic action
 * ********************************************************** */

typedef struct{
  struct sigaction sa;
  struct sigevent se;
  struct itimerspec is;
  timer_t id;
  bool is_running;
} liwPActionRT;

int liwPActionRTCreate(liwPActionRT *pa, int id, long int interval, void (* handler)(int,siginfo_t*,void*));
int liwPActionRTStart(liwPActionRT *pa);
int liwPActionRTStop(liwPActionRT *pa);

__END_DECLS

#endif /* __LIW_PACTION_H__ */

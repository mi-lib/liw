/* LIW - Linux Wizard
 * Copyright (C) 2000 Tomomichi Sugihara (Zhidao)
 */
/*! \file liw_lock.h
 * \brief process locking operation.
 * \author Zhidao
 */

#ifndef __LIW_LOCK_H__
#define __LIW_LOCK_H__

#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

#include <zeda/zeda.h>

__BEGIN_DECLS

/* ********************************************************** */
/* lockfile operation
 * ********************************************************** */

void liwLockInit(char filename[]);

bool liwLock(pid_t pid);
bool liwUnlock(pid_t pid);
void liwUnlockForce(int sig);

__END_DECLS

#endif /* __LIW_LOCK_H__ */

/* LIW - Linux Wizard
 * Copyright (C) 2000 Tomomichi Sugihara (Zhidao)
 */
/*! \file liw_coproc.h
 * \brief coprocess operation.
 * \author Zhidao
 */

#ifndef __LIW_COPROC_H__
#define __LIW_COPROC_H__

#include <zeda/zeda.h>

__BEGIN_DECLS

/* co-process execution */

void liwExecCmdFree(char **argv, int num);
int liwExecCmdParse(char *cmd, char ***argv);
int liwExec(char *cmd);

/* ********************************************************** */
/* CLASS: liwPipedCoproc
 * piped forked coprocess operator
 * ********************************************************** */

typedef struct{
  int pid;   /* process ID */
  int fd[2]; /* file descriptors for stdout and stdin */
  FILE *fp;
  char **argv;
} liwPipedCoproc;

int liwPipedCoprocOpenInput(liwPipedCoproc *proc, char *cmd);
int liwPipedCoprocOpenOutput(liwPipedCoproc *proc, char *cmd);
int liwPipedCoprocSendMsg(liwPipedCoproc *proc, char *fmt, ...);
int liwPipedCoprocClose(liwPipedCoproc *proc, char *msg);

__END_DECLS

#endif /* __LIW_COPROC_H__ */

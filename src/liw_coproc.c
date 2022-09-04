/* LIW - Linux Wizard
 * Copyright (C) 2000 Tomomichi Sugihara (Zhidao)
 *
 * liw_coproc - coprocess operation
 */

#include <unistd.h>
#include <stdarg.h>
#include <sys/wait.h>

#include <liw/liw_coproc.h>

/* co-process execution */

int liwExecCmdParse(char *cmd, char ***argv)
{
  char *cmddup, buf[BUFSIZ];
  char **argv_tmp;
  int num;

  if( ( cmddup = strdup( cmd ) ) == NULL ){
    ZALLOCERROR();
    return -1;
  }
  *argv = NULL;
  for( num=0; ; num++ ){
    if( ( argv_tmp = zRealloc( *argv, char *, num+1 ) ) == NULL ){
      ZALLOCERROR();
      liwExecCmdFree( *argv, num );
      return -1;
    }
    *argv = argv_tmp;
    if( zSToken( cmddup, buf, BUFSIZ ) ){
      if( ( (*argv)[num] = strdup( buf ) ) == NULL ){
        ZALLOCERROR();
        liwExecCmdFree( *argv, num );
        return -1;
      }
    } else{
      (*argv)[num] = NULL;
      break;
    }
  }
  free( cmddup );
  return num;
}

void liwExecCmdFree(char **argv, int num)
{
  int i;

  for( i=0; i<num; i++ ) free( argv[i] );
  free( argv );
}

int liwExec(char *cmd)
{
  char **argv;

  liwExecCmdParse( cmd, &argv );
  return execvp( argv[0], argv );
}

/* ********************************************************** */
/* CLASS: liwPipedCoproc
 * piped forked coprocess operator
 * ********************************************************** */

/* coprocess reads the parent process's stdout from stdin. */
int liwPipedCoprocOpenInput(liwPipedCoproc *proc, char *cmd)
{
  int pid;
  char **argv;

  liwExecCmdParse( cmd, &argv );

  if( pipe( proc->fd ) == -1 ){
    ZRUNERROR( "cannot create pipe" );
    return -1;
  }
  if( ( pid = fork() ) == -1 ){
    ZRUNERROR( "cannot create coprocess" );
    return -1;
  }
  if( pid == 0 ){
    dup2( proc->fd[0], 0 );
    close( proc->fd[0] );
    close( proc->fd[1] );
    execvp( argv[0], argv );
    _exit( -1 );
  }
  proc->pid = pid;
  close( proc->fd[0] );
  if( ( proc->fp = fdopen( proc->fd[1], "w" ) ) == NULL ){
    ZRUNERROR( "cannot reopen file descriptor" );
    return -1;
  }
  return 0;
}

/* coprocess writes to the parent process's stdin. */
int liwPipedCoprocOpenOutput(liwPipedCoproc *proc, char *cmd)
{
  int pid;
  char **argv;

  liwExecCmdParse( cmd, &argv );

  if( pipe( proc->fd ) == -1 ){
    ZRUNERROR( "cannot create pipe" );
    return -1;
  }
  if( ( pid = fork() ) == -1 ){
    ZRUNERROR( "cannot create coprocess" );
    return -1;
  }
  if( pid == 0 ){
    close( proc->fd[0] );
    dup2( proc->fd[1], 1 );
    close( proc->fd[1] );
    execvp( argv[0], argv );
    _exit( -1 );
  }
  proc->pid = pid;
  close( proc->fd[1] );
  if( ( proc->fp = fdopen( proc->fd[0], "r" ) ) == NULL ){
    ZRUNERROR( "cannot reopen file descriptor" );
    return -1;
  }
  return 0;
}

int liwPipedCoprocSendMsg(liwPipedCoproc *proc, char *fmt, ...)
{
  va_list args;

  va_start( args, fmt );
  vfprintf( proc->fp, fmt, args );
  fflush( proc->fp );
  va_end( args );
  return 0;
}

int liwPipedCoprocClose(liwPipedCoproc *proc, char *msg)
{
  int status;

  if( msg )
    liwPipedCoprocSendMsg( proc, msg ); /* message for termination */
  fclose( proc->fp );
  close( proc->fd[1] );
  waitpid( proc->pid, &status, 0 );
  return 0;
}

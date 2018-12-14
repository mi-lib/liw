/* LIW - Linux Wizard
 * Copyright (C) 2000 Tomomichi Sugihara (Zhidao)
 *
 * liw_lock - process locking operation
 */

#include <liw/liw_lock.h>

/* ********************************************************** */
/* lockfile operation
 * ********************************************************** */

static char lockfile[BUFSIZ];

/* METHOD:
 * liwLockInit
 * - set lockfile name
 */
void liwLockInit(char filename[])
{
  signal( SIGABRT, liwUnlockForce );
  signal( SIGHUP,  liwUnlockForce );
  signal( SIGINT,  liwUnlockForce );
  signal( SIGQUIT, liwUnlockForce );
  signal( SIGILL,  liwUnlockForce );

  strcpy( lockfile, filename );
}

/* METHOD:
 * liwLock
 * creation of a lock file by a process 'pid'.
 * return the true value if succeeded, or false otherwise.
 */
bool liwLock(pid_t pid)
{
  FILE *fp;

  if( access( lockfile, F_OK ) == 0 ){
    ZRUNERROR( "already locked" );
    return false;
  }
  if( ( fp = fopen( lockfile, "w" ) ) == NULL ){
    ZOPENERROR( lockfile );
    return false;
  }
  fprintf( fp, "%d", pid );
  fclose( fp );
  return true;
}

/* METHOD:
 * liwUnlock
 * - deletion of a lock file by a process 'pid'.
 * return the true value if succeeded, or false otherwise.
 */
bool liwUnlock(pid_t pid)
{
  FILE *fp;
  pid_t lockpid;

  if( ( fp = fopen( lockfile, "r" ) ) == NULL ){
    ZOPENERROR( lockfile );
    return false;
  }
  if( fscanf( fp, "%d", &lockpid ) != 1 );
  fclose( fp );
  if( lockpid != pid ){
    ZRUNERROR( "cannot unlock by different process" );
    return false;
  }
  if( access( lockfile, W_OK ) != 0 ){
    ZRUNERROR( "cannot remove lockfile" );
    return false;
  }
  unlink( lockfile );
  return true;
}

/* METHOD:
 * liwUnlockForce
 * force to delete a lock file.
 * this function will be called only when the process is
 * terminated invalidly.
 */
void liwUnlockForce(int sig)
{
  if( access( lockfile, W_OK ) == 0 )
    unlink( lockfile );
  else if( access( lockfile, R_OK ) == 0 ){
    ZRUNERROR( "illegal permission for lockfile" );
    exit(1);
  }
}

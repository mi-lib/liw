/* LIW - Linux Wizard
 * Copyright (C) 2000 Tomomichi Sugihara (Zhidao)
 *
 * liw_time - time management
 */

#include <liw/liw_time.h>
#include <errno.h>

/* fine sleep functions */

int liwSleep(long int sec, long int nsec)
{
  struct timespec req, rem;

  req.tv_sec = sec;
  req.tv_nsec = nsec;
  rem.tv_sec = 0;
  rem.tv_nsec = 0;
  while( nanosleep( &req, &rem ) ){
    if( errno == EINTR ){
      req.tv_sec = rem.tv_sec;
      req.tv_nsec = rem.tv_nsec;
    } else{
      ZRUNERROR( "invalid time specified." );
      return -1;
    }
  }
  return 0;
}

/* CPU clock frequency */

int liwCPUFreq(void)
{
  FILE *fp;
  char str[BUFSIZ];
  const char *cpuinfo = "/proc/cpuinfo";
  int freq = 0;

  if( !( fp = fopen( cpuinfo, "r" ) ) ){
    ZRUNERROR( "fatal error. %s doesn't exist!", cpuinfo );
    return 0;
  }
  while( !feof( fp ) ){
    if( !fgets( str, BUFSIZ, fp ) ) break;
    if( strncmp( str, "cpu MHz", 7 ) == 0 ) break;
  }
  fclose( fp );
  zSInt( &str[7], &freq );
  return freq;
}

double liwCPURate(void)
{
  return 1.0e-6 / liwCPUFreq();
}

/* get the current time stamp */

long long liwNow(void)
{
  struct timeval tv;

  gettimeofday( &tv, NULL );
  return tv_usec( &tv );
}

/* get the current time stamp in second */

double liwNowF(void)
{
  struct timeval tv;

  gettimeofday( &tv, NULL );
  return tv_sec( &tv );
}

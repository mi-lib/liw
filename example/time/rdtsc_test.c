#include <sys/time.h>
#include <unistd.h>
#include <liw/liw_time.h>

int main(void)
{
  unsigned long long t1, t2, t3, t4;
  struct timeval tv;
  double rate;

  rate = liwCPURate();
  t1 = liwClock();
  usleep( 1000000 );
  t2 = liwClock();
  gettimeofday( &tv, NULL );
  t3 = liwClock();
  t4 = liwClock();
  printf( "%g\n", ( t2 - t1 ) * rate );
  printf( "%g\n", ( t3 - t2 ) * rate );
  printf( "%g\n", ( t4 - t3 ) * rate );
  return 0;
}

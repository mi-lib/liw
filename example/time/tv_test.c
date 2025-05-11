#include <unistd.h>
#include <liw/liw_time.h>

#define N 1000

int main(int argc, char *argv[])
{
  int i;
  struct timeval tv;
  double t;
  long long ut, ut2;

  for( i=0; i<N; i++ ){
    gettimeofday( &tv, NULL );
    t = tv_sec( &tv );
    ut = tv_usec( &tv );
    ut2 = sec2usec( t );
    printf( "%llu[usec] %lld[usec] %f[sec]\n", ut, ut2, t );
    usleep( 1000 );
  }
  return 0;
}

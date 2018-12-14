#include <liw/liw_time.h>

int main(int argc, char *argv[])
{
  if( argc < 2 ){
    eprintf( "%s: enter microsecond value.\n", argv[0] );
    return 1;
  }
  printf( "%f\n", sec2usec( usec2sec( atof(argv[1]) ) ) );
  return 0;
}

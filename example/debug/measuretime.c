#include <liw/liw_debug.h>

int main(void)
{
  long clk;
  double sec;

  printf( ">>execution time measurement<<\n" );
  MEASURE_EXEC_CLOCK( &clk, {
    printf( "gahaha\n" );
  } );
  MEASURE_EXEC_SEC( &sec, {
    printf( "gahaha\n" );
  } );
  printf( "%ld %f\n", clk, sec );
  return 0;
}

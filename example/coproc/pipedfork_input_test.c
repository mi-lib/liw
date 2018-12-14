#include <unistd.h>
#include <liw/liw_coproc.h>

#define PI 3.1415926
#define T 20

int main(void)
{
  liwPipedCoproc proc;
  int i;

  liwPipedCoprocOpenInput( &proc, "gnuplot" );
  for( i=1; i<T; i++ ){
    liwPipedCoprocSendMsg( &proc,
      "plot [0:%d][-1:1] sin(2*%f*x*%d/%d)*sin(%f*x/%d)\n",
      T, PI, i, T, PI, T );
    usleep( 100000 );
  }
  getchar();
  liwPipedCoprocClose( &proc, "quit" );

  return 0;
}

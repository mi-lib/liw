#include <unistd.h>
#include <liw/liw_coproc.h>

int main(void)
{
  liwPipedCoproc proc;
  char str[BUFSIZ];

  liwPipedCoprocOpenOutput( &proc, "echo hoge" );
  if( fgets( str, BUFSIZ, proc.fp ) == 0 );
  liwPipedCoprocClose( &proc, NULL );
  printf( "read from coprocess --- %s", str );
  return 0;
}

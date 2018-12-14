#include <liw/liw_dl.h>

int main(void)
{
  liwDL plugin;
  void (*f)(void);

  if( !liwDLOpen( &plugin, "./plugin/plugin1.plg" ) ) exit( 1 );
  if( ( f = liwDLSymbol( &plugin, "foo" ) ) ){
    printf( "function address = %p\n", f );
    f();
  }
  liwDLClose( &plugin );
  return 0;
}

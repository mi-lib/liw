#include <liw/liw_dl.h>

int main(void)
{
  liwDLList list;
  void (*f)(void);

  liwDLListOpen( &list, "./plugin", "plg" );
  if( ( f = liwDLListSymbol( &list, "foo" ) ) ){
    printf( "function address = %p\n", f );
    f();
  }
  liwDLListPurge( &list, "./plugin/plugin2.plg" );
  if( ( f = liwDLListSymbol( &list, "foo" ) ) ){
    printf( "function address = %p\n", f );
    f();
  }
  liwDLListClose( &list );
  return 0;
}

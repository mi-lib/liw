#include <liw/liw_dl.h>

int main(void)
{
  liwDLList list;
  void (*f)(void);

  zListInit( &list );

  printf( "[add plugin1]\n" );
  liwDLListAdd( &list, "./plugin/plugin1.plg" );
  if( ( f = liwDLListSymbol( &list, "foo" ) ) ) f();
  printf( "[add plugin2]\n" );
  liwDLListAdd( &list, "./plugin/plugin2.plg" );
  if( ( f = liwDLListSymbol( &list, "foo" ) ) ) f();
  printf( "[purge plugin1]\n" );
  liwDLListPurge( &list, "./plugin/plugin2.plg" );
  if( ( f = liwDLListSymbol( &list, "foo" ) ) ) f();
  printf( "[purge plugin2]\n" );
  liwDLListPurge( &list, "./plugin/plugin1.plg" );
  if( ( f = liwDLListSymbol( &list, "foo" ) ) ) f();

  liwDLListClose( &list );
  return 0;
}

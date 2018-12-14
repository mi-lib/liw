#include <liw/liw_dl.h>

int main(void)
{
  liwDLAPIList api_list;
  void (*f)(void);

  liwDLAPIListOpen( &api_list, "./plugin", "plg", "liw_dl_api" );

  if( ( f = liwDLAPIListFind( &api_list, "foo", NULL ) ) ){
    printf( "function address = %p\n", f );
    f();
  }
  if( ( f = liwDLAPIListFind( &api_list, "baa", NULL ) ) ){
    printf( "function address = %p\n", f );
    f();
  }

  liwDLAPIListClose( &api_list );
  return 0;
}

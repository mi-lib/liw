#include <liw/liw_dl.h>

liwDLAPI liw_dl_api[] = {
  { "foo", "baa", 0 },
  { NULL, NULL, 0 },
};

void foo(void)
{
  printf( "baa\n" );
}

LIW_DL_INIT{
  printf( "%s plugin2: plugged-in\n", __FUNCTION__ );
  printf( "foo() address = %p\n", foo );
}

LIW_DL_EXIT{
  printf( "%s plugin2: plugged-out\n", __FUNCTION__ );
}

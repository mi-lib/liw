#define _GNU_SOURCE
#include <liw/liw_dl.h>

liwDLAPI liw_dl_api[] = {
  { "foo", "foo", 0 },
  { NULL, NULL, 0 },
};

void foo(void)
{
  printf( "foo\n" );
}

LIW_DL_INIT{
  printf( "%s plugin1: plugged-in\n", __FUNCTION__ );
  printf( "foo() address = %p\n", foo );
}

LIW_DL_EXIT{
  printf( "%s plugin1: plugged-out\n", __FUNCTION__ );
}

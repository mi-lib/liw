#include <liw/liw_coproc.h>

int main(void)
{
  return liwExec( "ls -laF --color=auto ./" );
}

#include "msq.h"

int main(void)
{
  int id;
  struct msg_t data;

  if( ( id = liwMSQGet( MSQNAME ) ) == -1 ) exit( 1 );

  while( 1 ){
    if( liwMSQReceive( id, (void *)&data, SIZ, 0 ) == 0 ) exit( 1 );
    printf( "received: %s\n", data.text );
    if( !strncmp( data.text, MSQ_QUIT, strlen(MSQ_QUIT) ) ) break;
  }
  liwMSQDestroy( id );
  return 0;
}

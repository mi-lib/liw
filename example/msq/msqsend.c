#include "msq.h"

int main(void)
{
  int id;
  struct msg_t data;

  if( ( id = liwMSQGet( MSQNAME ) ) == -1 ) exit( 1 );

  printf( "to quit msq test, enter the string 'quit'.\n" );
  while( 1 ){
    printf( "enter string:" );
    data.msg_type = 1;
    if( !fgets( data.text, SIZ, stdin ) );
    data.text[strlen(data.text)-1] = '\0';
    printf( "string: %s\n", data.text );

    if( liwMSQSend( id, (void *)&data, SIZ ) == 0 ) exit( 1 );
    if( !strncmp( data.text, MSQ_QUIT, strlen(MSQ_QUIT) ) ) break;
  }
  return 0;
}

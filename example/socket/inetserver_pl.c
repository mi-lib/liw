#include <liw/liw_socket.h>
#include <pthread.h>

void server(int port)
{
  int sfd, cfd;
  char buf[BUFSIZ];

  if( ( sfd = liwSocketINETBind( "127.0.0.1", port, SOCK_STREAM, 1 ) ) == 0 )
    pthread_exit( (void *)1 );

  while( 1 ){
    if( ( cfd = liwSocketINETAccept( sfd ) ) == -1 )
      pthread_exit( (void *)1 );

    printf( "%d %d:%d", port, sfd, cfd );
    printf( "server is waiting...\n" );
    memset( buf, 0, BUFSIZ );
    if( read( cfd, buf, BUFSIZ ) == 0 );
    printf( "read string : %s\n", buf );
    sprintf( &buf[strlen(buf)], "[%d]", port );
    if( write( cfd, buf, BUFSIZ ) == 0 );
    if( !strncmp( buf, "quit", 4 ) ) break;
    usleep( 20000 ); /* 20[msec] */
    close( cfd );
  }
  close( sfd );
  pthread_exit( (void *)0 );
}

int main(void)
{
  pthread_t thread[2];

  pthread_create( &thread[0], NULL, (void *)server, (void *)3000 );
  pthread_create( &thread[1], NULL, (void *)server, (void *)6000 );
  pthread_join( thread[0], NULL );
  pthread_join( thread[1], NULL );
  return 0;
}

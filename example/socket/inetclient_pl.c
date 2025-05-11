#include <liw/liw_socket.h>
#include <pthread.h>

void client(int port)
{
  int fd;
  char buf[BUFSIZ];
  int i, n;

  n = port / 300;
  for( i=0; i<n; i++ ){
    if( !( fd = liwSocketINETConnect( "127.0.0.1", port, SOCK_STREAM ) ) )
      pthread_exit( (void *)1 );

    memset( buf, 0, BUFSIZ );
    if( i == n - 1 )
      sprintf( buf, "quit %d", port );
    else
      sprintf( buf, "[%d/%d] via %d", i, n, port );
    if( write( fd, buf, BUFSIZ ) == 0 );
    if( read( fd, buf, BUFSIZ ) == 0 );
    printf( "returned string = %s\n", buf );
    close( fd );
  }
  pthread_exit( (void *)0 );
}

int main(void)
{
  pthread_t thread[2];

  pthread_create( &thread[0], NULL, (void *)client, (void *)3000 );
  pthread_create( &thread[1], NULL, (void *)client, (void *)6000 );
  pthread_join( thread[0], NULL );
  pthread_join( thread[1], NULL );
  return 0;
}

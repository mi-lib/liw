/* LIW - Linux Wizard
 * Copyright (C) 2000 Tomomichi Sugihara (Zhidao)
 *
 * liw_fifo - FIFO communication
 */

#include <liw/liw_fifo.h>

/* ********************************************************** */
/* CATEGORY: FIFO utilities
 * FIFO management macroes and functions
 * ********************************************************** */

/* METHOD: int liwFIFOOpen(char fifoname[], int mode)
 * - open FIFO 'fifoname'.
 * return the file discriptor for the FIFO.
 */
int liwFIFOOpen(char fifoname[], int mode)
{
  int fd;

  if( access( fifoname, F_OK ) == -1 )
    if( mkfifo( fifoname, 0777 ) == 0 )
      eprintf( "FIFO %s has created.\n", fifoname );
  if( ( fd = open( fifoname, mode ) ) == -1 ){
    ZRUNERROR( "cannot open FIFO %s", fifoname );
    return LIW_FIFO_INVALID;
  }
  return fd;
}

/* METHOD: liwFIFOWrite
 * write a 'packet' to the file discripted by 'fd'.
 * return a written byte size.
 */
int liwFIFOWrite(int fd, void *packet, uint size)
{
  int byte;

  if( ( byte = write( fd, packet, size ) ) == -1 ){
    ZRUNERROR( "write failure through FIFO" );
    return LIW_FIFO_INVALID;
  }
  return byte;
}

/* METHOD: liwFIFORead
 * read a 'packet' from the file discripted by 'fd'.
 * return a read byte size.
 */
int liwFIFORead(int fd, void *packet, uint size)
{
  int byte;

  if( ( byte = read( fd, packet, size ) ) == -1 ){
    ZRUNERROR( "read failure from FIFO" );
    return LIW_FIFO_INVALID;
  }
  return byte;
}

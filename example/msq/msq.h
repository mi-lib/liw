#ifndef __MSQ_SAMPLE_H__
#define __MSQ_SAMPLE_H__

#include <liw/liw_ipc.h>

#define SIZ 128

struct msg_t{
  LIW_MSQ_PACKET;
  char text[SIZ];
};

#define MSQNAME "z_msq"
#define MSQ_QUIT "quit"

#endif /* __MSQ_SAMPLE_H__ */

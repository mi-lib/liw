/* LIW - Linux Wizard
 * Copyright (C) 2000 Tomomichi Sugihara (Zhidao)
 */
/*! \file liw_fifo.h
 * \brief FIFO communication
 * \author Zhidao
 */

#ifndef __LIW_FIFO_H__
#define __LIW_FIFO_H__

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <zeda/zeda.h>

__BEGIN_DECLS

/* ********************************************************** */
/* CATEGORY: FIFO utilities
 * FIFO management macroes and functions
 * ********************************************************** */

int liwFIFOOpen(char fifoname[], int mode);
#define liwFIFOWriteOpen(f)  liwFIFOOpen( f, O_WRONLY )
#define liwFIFOReadOpen(f)   liwFIFOOpen( f, O_RDONLY )

#define liwFIFOClose(fd)  close(fd)
#define liwFIFODestroy(f) unlink( f )

#define LIW_FIFO_INVALID (-1)

int liwFIFOWrite(int fd, void *packet, uint size);
int liwFIFORead(int fd, void *packet, uint size);

__END_DECLS

#endif /* __LIW_FIFO_H__ */

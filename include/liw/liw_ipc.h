/* LIW - Linux Wizard
 * Copyright (C) 2000 Tomomichi Sugihara (Zhidao)
 */
/*! \file liw_ipc.h
 * \brief System V IPC (semaphore, shared memory, message queue)
 * \author Zhidao
 */

#ifndef __LIW_SYSVIPC_H__
#define __LIW_SYSVIPC_H__

#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>

#include <zeda/zeda.h>

#define liwIPCKey(s) (key_t)ftok( (s), 0 )

__BEGIN_DECLS

/* ********************************************************** */
/* CLASS: liwSEM
 * semaphore operation
 * ********************************************************** */

#if _SEM_SEMUN_UNDEFINED == 1
union semun{
  int val;
  struct semid_ds *buf;
  unsigned short *array;
  struct seminfo *__buf;
};
#endif

bool liwSEMCreate(int id);
bool liwSEMDestroy(int id);
int liwSEMGet(char *key);

bool liwSEMOperate(int id, short dv);

#define LIW_SEM_PASSEREN  (-1)
#define LIW_SEM_VRIJGEVEN ( 1)

#define liwSEMPasseren(i)  liwSEMOperate( i, LIW_SEM_PASSEREN )
#define liwSEMVrijgeven(i) liwSEMOperate( i, LIW_SEM_VRIJGEVEN )

/* ********************************************************** */
/* CLASS: liwSHM
 * shared memory management
 * ********************************************************** */

typedef struct{
  int id;
  unsigned size;
  void *mp;
} liwSHM;

int liwSHMModeAttach(liwSHM *shm, char *key, int size, int mode);

#define liwSHMWriteAttach(m,k,s)  liwSHMModeAttach((m),(k),(s),0222)
#define liwSHMReadAttach(m,k,s)   liwSHMModeAttach((m),(k),(s),0444)
#define liwSHMAttach(m,k,s)       liwSHMModeAttach((m),(k),(s),0666)

#define liwSHMModeCreate(m,k,s,p) liwSHMModeAttach(m,k,s,IPC_CREAT|p)
#define liwSHMCreate(m,k,s)       liwSHMModeCreate(m,k,s,0666)

/*! \brief allocate shared memory.
 *
 * liwSHMModeAlloc() allocates shared memory indicated with \a key
 * on \a mode.
 * \a size is the size to allocate.
 * \a shm is a pointer to the shared memory management instance.
 * \retval
 * The value returned is the ID which indicates \a shm->mp.
 */
int liwSHMModeAlloc(liwSHM *shm, char *key, int size, int mode);

#define liwSHMWriteAlloc(m,k,s)   liwSHMModeAlloc((m),(k),(s),0222)
#define liwSHMReadAlloc(m,k,s)    liwSHMModeAlloc((m),(k),(s),0444)
#define liwSHMAlloc(m,k,s)        liwSHMModeAlloc((m),(k),(s),0666)

/*! \brief clear shared memory space.
 *
 * liwSHMClear() clears the memory space indicated by \a shm.
 */
void liwSHMClear(liwSHM *shm);

/*! \brief detach shared memory.
 *
 * liwSHMDetach() detaches the shared memory indicated with \a id.
 * \retval
 * liwSHMDetach() returns the true value if succeed.
 */
bool liwSHMDetach(liwSHM *shm);

/*! \brief destroy shared memory.
 *
 * liwSHMDestroy() destroys the shared memory indicated with \a id.
 * \retval
 * liwSHMDestroy() returns the true value if succeed.
 */
bool liwSHMDestroy(liwSHM *shm);

/* ********************************************************** */
/* CLASS: liwMSQ
 * message queue operation
 * ********************************************************** */

/* all structs transfered through msq must have
 * long integer type member at the head.
 */
#define LIW_MSQ_PACKET long int msg_type

int liwMSQGet(char *key);

int liwMSQSend(int id, void *data, int size);
int liwMSQReceive(int id, void *data, int size, int type);

bool liwMSQDestroy(int id);

__END_DECLS

#endif /* __LIW_SYSVIPC_H__ */

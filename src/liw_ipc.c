/* LIW - Linux Wizard
 * Copyright (C) 2000 Tomomichi Sugihara (Zhidao)
 *
 * liw_ipc - System V IPC (semaphore, shared memory, message queue)
 */

#include <liw/liw_ipc.h>
#include <errno.h>
#include <string.h>

/* ********************************************************** */
/* CLASS: liwSEM
 * semaphore operation
 * ********************************************************** */

bool liwSEMCreate(int id)
{
  union semun sem_union;

  sem_union.val = 1;
  if( semctl( id, 0, SETVAL, sem_union ) == -1 ){
    ZRUNERROR( "cannot create semaphore (ID=%d)", id );
    return false;
  }
  return true;
}

bool liwSEMDestroy(int id)
{
  union semun sem_union;

  if( semctl( id, 0, IPC_RMID, sem_union ) == -1 ){
    ZRUNERROR( "cannot delete semaphore (ID=%d)", id );
    return false;
  }
  return true;
}

int liwSEMGet(char *key)
{
  return semget( liwIPCKey(key), 1, 0666 | IPC_CREAT );
}

bool liwSEMOperate(int id, short dv)
{
  struct sembuf sem_b;

  sem_b.sem_num = 0;
  sem_b.sem_op = dv;
  sem_b.sem_flg = SEM_UNDO;
  if( semop( id, &sem_b, 1 ) == -1 ){
    ZRUNERROR( "failed to operate semaphore (ID=%d)", id );
    return false;
  }
  return true;
}

/* ********************************************************** */
/* CLASS: liwSHM
 * shared memory management
 * ********************************************************** */

int liwSHMModeAttach(liwSHM *shm, char *key, int size, int mode)
{
  if( ( shm->id = shmget( liwIPCKey(key), size, mode ) ) < 0 ){
    if( mode & IPC_CREAT )
      ZALLOCERROR();
    return -1;
  }
  if( ( shm->mp = shmat( shm->id, NULL, 0 ) ) < 0 ){
    ZRUNERROR( "cannot attach to shared memory (ID=%d)", shm->id );
    return -1;
  }
  shm->size = size;
  return shm->id;
}

int liwSHMModeAlloc(liwSHM *shm, char *key, int size, int mode)
{
  return ( liwSHMModeAttach( shm, key, size, mode ) < 0 ) ?
    liwSHMModeCreate( shm, key, size, mode ) : -1;
}

void liwSHMClear(liwSHM *shm)
{
  memset( shm->mp, 0, shm->size );
}

bool liwSHMDetach(liwSHM *shm)
{
  if( shmdt( shm->mp ) < 0 ){
    ZRUNERROR( "cannot detach shared memory (ID=%d)", shm->id );
    return false;
  }
  return true;
}

bool liwSHMDestroy(liwSHM *shm)
{
  if( shmctl( shm->id, IPC_RMID, NULL ) < 0 ){
    ZRUNERROR( "cannot remove shared memory (ID=%d)", shm->id );
    return false;
  }
  return true;
}

/* ********************************************************** */
/* CLASS: liwMSQ
 * message queue operation
 * ********************************************************** */

int liwMSQGet(char *key)
{
  int id;

  if( ( id = msgget( liwIPCKey(key), IPC_CREAT|0666 ) ) == -1 )
    ZRUNERROR( "cannot get message queue" );
  return id;
}

int liwMSQSend(int id, void *data, int size)
{
  if( msgsnd( id, data, size, 0 ) == -1 ){
    ZRUNERROR( "cannot send message queue (ID=%d)", id );
    return 0;
  }
  return size;
}

int liwMSQReceive(int id, void *data, int size, int type)
{
  if( msgrcv( id, data, size, type, 0 ) == -1 ){
    ZRUNERROR( "cannot receive message queue (ID=%d)", id );
    return 0;
  }
  return size;
}

bool liwMSQDestroy(int id)
{
  if( msgctl( id, IPC_RMID, NULL ) == -1 ){
    ZRUNERROR( "cannot remove message queue (ID=%d)", id );
    return false;
  }
  return true;
}

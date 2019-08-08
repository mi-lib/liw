/* LIW - Linux Wizard
 * Copyright (C) 2000 Tomomichi Sugihara (Zhidao)
 */
/*! \file liw_dl.h
 * \brief dynamic link architecture.
 * \author Zhidao
 */

#ifndef __LIW_DL_H__
#define __LIW_DL_H__

#include <dlfcn.h>
#include <zeda/zeda.h>

__BEGIN_DECLS

/* ********************************************************** */
/* initializer and terminator
 * ********************************************************** */

#define LIW_DL_INIT \
  static void __attribute__((constructor)) __liw_dl_init(void)
#define LIW_DL_EXIT \
  static void __attribute__((destructor))  __liw_dl_exit(void)

/* ********************************************************** */
/* CLASS: liwDL
 * plug-in
 * ********************************************************** */

typedef void *liwDLHandle;
typedef struct{
  Z_NAMED_CLASS
  liwDLHandle handle;
} liwDL;

bool liwDLOpen(liwDL *plugin, char filename[]);
#define liwDLClose(p) do{\
  dlclose( (p)->handle );\
  zNameFree( p );\
} while(0)

#define _liwDLSymbol(p,s) dlsym( (p)->handle, (s) )
liwDLHandle liwDLSymbol(liwDL *plugin, char *symbol);

/* ********************************************************** */
/* CLASS: liwDLList
 * plug-in list
 * ********************************************************** */

zListClass(liwDLList, liwDLListCell, liwDL);

bool liwDLListOpen(liwDLList *list, char path[], char *suffix);
void liwDLListClose(liwDLList *list);
#define _liwDLListCellSymbol(c,s) _liwDLSymbol( &(c)->data, (s) )
#define liwDLListCellSymbol(c,s) liwDLSymbol( &(c)->data, (s) )

bool liwDLListAdd(liwDLList *list, char *pathname);
liwDLListCell *liwDLListFind(liwDLList *list, char *name);
void liwDLListPurge(liwDLList *list, char *name);

liwDLHandle liwDLListSymbol(liwDLList *list, char *symbol);

/* ********************************************************** */
/* CLASS: liwDLAPI & liwDLAPIList
 * plug-in list
 * ********************************************************** */

typedef struct{
  Z_NAMED_CLASS
  char *label;
  int argc;
} liwDLAPI;

liwDLHandle liwDLAPIFind(liwDL *plugin, liwDLAPI api[], char *label, int *argc);

typedef struct{
  liwDL plugin;
  liwDLAPI *api;
} liwDLAPIData;
zListClass(liwDLAPIList, liwDLAPIListCell, liwDLAPIData);

bool liwDLAPIListAdd(liwDLAPIList *list, char *name, char *api);
bool liwDLAPIListOpen(liwDLAPIList *list, char path[], char *suffix, char *api);
void liwDLAPIListClose(liwDLAPIList *list);

liwDLHandle liwDLAPIListFind(liwDLAPIList *list, char *label, int *argc);

__END_DECLS

#endif /* __LIW_DL_H__ */

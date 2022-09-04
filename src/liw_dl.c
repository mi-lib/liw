/* LIW - Linux Wizard
 * Copyright (C) 2000 Tomomichi Sugihara (Zhidao)
 *
 * liw_dl - dynamic link architecture
 */

#include <liw/liw_dl.h>
#include <dirent.h>

/* ********************************************************** */
/* CLASS: liwDLHandle
 * plug-in handler
 * ********************************************************** */

bool liwDLOpen(liwDL *plugin, char filename[])
{
  if( !( plugin->handle = dlopen( filename, RTLD_NOW | RTLD_GLOBAL ) ) ){
    ZRUNERROR( "%s", dlerror() );
    return false;
  }
  zNameSet( plugin, filename );
  return true;
}

liwDLHandle liwDLSymbol(liwDL *plugin, char *symbol)
{
  liwDLHandle sym;
  char *error;

  dlerror(); /* clear the previous error message */
  sym = _liwDLSymbol( plugin, symbol );
  if( ( error = dlerror() ) ){
    ZRUNERROR( "%s", error );
    return NULL;
  }
  return sym;
}

/* ********************************************************** */
/* CLASS: liwDLList
 * plug-in list
 * ********************************************************** */

bool liwDLListOpen(liwDLList *list, char path[], char *suffix)
{
  int num, i;
  struct dirent **entry;
  char *sfx, pluginname[BUFSIZ];
  bool result = true;

  zListInit( list );
  /* scan path */
  if( ( num = scandir( path, &entry, 0, alphasort ) ) < 0 ){
    ZRUNERROR( "cannot scan directory %s", path );
    return false;
  }
  /* open plug-in */
  for( i=0; i<num; i++ ){
    sfx = zGetSuffix( entry[i]->d_name );
    if( sfx && !strcmp( sfx, suffix ) ){
      /* allocation of plug-in cell */
      sprintf( pluginname, "%s/%s", path, entry[i]->d_name );
      if( !liwDLListAdd( list, pluginname ) ){
        liwDLListClose( list );
        result = false;
        break;
      }
    }
  }
  /* destruction of path entry */
  zFree( entry );
  return result;
}

void liwDLListClose(liwDLList *list)
{
  liwDLListCell *cp;

  zListForEachRew( list, cp ) /* backward closing */
    if( cp->data.handle ) liwDLClose( &cp->data );
  zListDestroy( liwDLListCell, list );
}

bool liwDLListAdd(liwDLList *list, char *pathname)
{
  liwDLListCell *cp;

  if( !( cp = zAlloc( liwDLListCell, 1 ) ) ){
    ZALLOCERROR();
    return false;
  }
  if( !liwDLOpen( &cp->data, pathname ) ) return false;
  zListInsertHead( list, cp );
  return true;
}

liwDLListCell *liwDLListFind(liwDLList *list, char *name)
{
  liwDLListCell *cp;

  zListForEachRew( list, cp )
    if( !strcmp( zNamePtr(&cp->data), name ) ) return cp;
  return NULL;
}

void liwDLListPurge(liwDLList *list, char *name)
{
  liwDLListCell *cp;

  if( !( cp = liwDLListFind( list, name ) ) ){
    ZRUNERROR( "plugin %s not found", name );
    return;
  }
  zListPurge( list, cp );
  liwDLClose( &cp->data );
  zFree( cp );
}

liwDLHandle liwDLListSymbol(liwDLList *list, char *symbol)
{
  liwDLListCell *cp;
  liwDLHandle handle;

  zListForEachRew( list, cp )
    if( ( handle = _liwDLListCellSymbol( cp, symbol ) ) ) return handle;
  return NULL;
}

/* ********************************************************** */
/* CLASS: liwDLAPI & liwDLAPIList
 * plug-in list
 * ********************************************************** */

liwDLHandle liwDLAPIFind(liwDL *plugin, liwDLAPI api[], char *label, int *argc)
{
  liwDLAPI *ap;

  for( ap=api; zNamePtr(ap); ap++ )
    if( !strcmp( ap->label, label ) ){
      if( argc ) *argc = ap->argc;
      return liwDLSymbol( plugin, ap->name );
    }
  return NULL;
}

bool liwDLAPIListAdd(liwDLAPIList *list, char *name, char *api)
{
  liwDLAPIListCell *cp;

  if( !( cp = zAlloc( liwDLAPIListCell, 1 ) ) ){
    ZALLOCERROR();
    return false;
  }
  liwDLOpen( &cp->data.plugin, name );
  cp->data.api = liwDLSymbol( &cp->data.plugin, api );
  zListInsertTail( list, cp );
  return true;
}

bool liwDLAPIListOpen(liwDLAPIList *list, char path[], char *suffix, char *api)
{
  int num, i;
  struct dirent **entry;
  char *sfx, pluginname[BUFSIZ];
  bool result = true;

  zListInit( list );
  /* scan path */
  if( ( num = scandir( path, &entry, 0, alphasort ) ) < 0 ){
    ZRUNERROR( "cannot scan directory %s", path );
    return false;
  }
  /* open plug-in */
  for( i=0; i<num; i++ ){
    sfx = zGetSuffix( entry[i]->d_name );
    if( sfx && !strcmp( sfx, suffix ) ){
      /* allocation of plug-in cell */
      sprintf( pluginname, "%s/%s", path, entry[i]->d_name );
      if( !liwDLAPIListAdd( list, pluginname, api ) ){
        liwDLAPIListClose( list );
        result = false;
        break;
      }
    }
  }
  /* destruction of path entry */
  zFree( entry );
  return result;
}

void liwDLAPIListClose(liwDLAPIList *list)
{
  liwDLAPIListCell *cp;

  zListForEachRew( list, cp )
    if( cp->data.plugin.handle ) liwDLClose( &cp->data.plugin );
  zListDestroy( liwDLAPIListCell, list );
}

liwDLHandle liwDLAPIListFind(liwDLAPIList *list, char *label, int *argc)
{
  liwDLAPIListCell *cp;
  liwDLHandle handle;

  zListForEachRew( list, cp )
    if( ( handle = liwDLAPIFind( &cp->data.plugin, cp->data.api, label, argc ) ) )
      return handle;
  return NULL;
}

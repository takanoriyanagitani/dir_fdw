#pragma once

#include <foreign/foreign.h>
#include <commands/defrem.h>

typedef struct DirFdwOption {
  const char* dirname;
  char        filter;
} DirFdwOption;

static void dir_fdw_options(Oid tableid, DirFdwOption* o){
  ForeignTable* t = GetForeignTable(tableid);
  ListCell* i = NULL;
  //char* filter = NULL;

  foreach(i, t->options){
    DefElem* d = lfirst(i);
    switch(d->defname[0]){
      case 'd':
        o->dirname = defGetString(d);
        break;
      /*
      case 'f':
        filter = defGetString(d);
        o->filter = NULL == filter ? '\0' : filter[0];
        break;
      */
      default: continue;
    }
  }
}

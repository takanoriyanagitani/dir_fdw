#pragma once

#include <postgres.h>

#include <foreign/fdwapi.h>
#include <access/reloptions.h>
#include <commands/defrem.h>
#include <catalog/pg_foreign_table.h>

Datum dir_fdw_validator(PG_FUNCTION_ARGS){
  Datum     arr = PG_GETARG_DATUM(0);
  Oid       oid = PG_GETARG_OID(1);
  List*     lst = untransformRelOptions(arr);
  ListCell* i   = NULL;

  const char* dirname = NULL;

  foreach(i, lst){
    DefElem*    d       = (DefElem*) lfirst(i);
    const char* optname = d->defname;
    switch(optname[0]){
      case 'd':
        dirname = defGetString(d);
        break;
      default:
        ereport(ERROR, (
          errcode(ERRCODE_FDW_INVALID_OPTION_NAME),
          errmsg("invalid option: %s", optname)
        ));
        break;
    }
  }

  switch(ForeignTableRelationId == oid && NULL == dirname){
    case true:
      ereport(ERROR, (
        errcode(ERRCODE_FDW_DYNAMIC_PARAMETER_VALUE_NEEDED),
        errmsg("dirname required.")
      ));
      break;
    default: break;
  }

  PG_RETURN_VOID();
}

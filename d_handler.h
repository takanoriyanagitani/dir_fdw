#pragma once

#include <postgres.h>

#include <foreign/fdwapi.h>

#include "d_relsize.h"
#include "d_path.h"
#include "d_plan.h"
#include "d_explain.h"
#include "d_begin.h"
#include "d_iterate.h"
#include "d_rescan.h"
#include "d_end.h"

Datum dir_fdw_handler(PG_FUNCTION_ARGS){
  FdwRoutine* r = makeNode(FdwRoutine);

  r->GetForeignRelSize  = dir_fdw_relsize;
  r->GetForeignPaths    = dir_fdw_path;
  r->GetForeignPlan     = dir_fdw_plan;
  r->ExplainForeignScan = dir_fdw_explain;
  r->BeginForeignScan   = dir_fdw_begin;
  r->IterateForeignScan = dir_fdw_iterate;
  r->ReScanForeignScan  = dir_fdw_rescan;
  r->EndForeignScan     = dir_fdw_end;

  PG_RETURN_POINTER(r);
}

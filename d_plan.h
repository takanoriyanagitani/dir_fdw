#pragma once

#include <optimizer/planmain.h>

static ForeignScan* dir_fdw_plan(
  PlannerInfo* p,
  RelOptInfo*  r,
  Oid          o,
  ForeignPath* f,
  List*        l,
  List*        s,
  Plan*        outer
){
  return make_foreignscan(
    l,
    s,
    r->relid,
    NIL, // no expressions to evaluate
    f->fdw_private,
    NIL, // no custom tlist
    NIL, // no remote quals
    outer
  );
}

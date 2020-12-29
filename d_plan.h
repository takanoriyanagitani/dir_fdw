#pragma once

#include <optimizer/planmain.h>
#include <optimizer/restrictinfo.h>

static ForeignScan* dir_fdw_plan(
  PlannerInfo* p,
  RelOptInfo*  r,
  Oid          o,
  ForeignPath* f,
  List*        l,
  List*        s,
  Plan*        outer
){
  s = extract_actual_clauses(s, false);
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

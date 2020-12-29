#pragma once

#include <optimizer/paths.h>
#include <optimizer/pathnode.h>

static void dir_fdw_estimate_cost(
  PlannerInfo* p, RelOptInfo* r, DirFdwPlanState* s, Cost* c, Cost* t
){
  Cost cpu = cpu_tuple_cost * 10 + r->baserestrictcost.per_tuple;
  Cost run = seq_page_cost * s->pages;
  run += cpu * s->ntup;
  *c = r->baserestrictcost.startup;
  *t = *c + run;
}

static void dir_fdw_path(PlannerInfo* p, RelOptInfo* r, Oid o){
  DirFdwPlanState* s = r->fdw_private;
  Cost start;
  Cost total;
  dir_fdw_estimate_cost(p, r, s, &start, &total);
  add_path(r, (Path*)create_foreignscan_path(
    p,
    r,
    NULL, // default pathtarget
    r->rows,
    start,
    total,
    NIL, // no pathkeys
    r->lateral_relids,
    NULL, // no extra plan
    NIL   // 
  ));
}

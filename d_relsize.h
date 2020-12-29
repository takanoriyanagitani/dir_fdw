#pragma once

#include <optimizer/optimizer.h>

static double dir_fdw_estimate(
  PlannerInfo* p, RelOptInfo* r, DirFdwPlanState* s
){
  BlockNumber pages = 8;
  s->pages = pages;
  for(; r && 0 <= r->tuples && 0 < r->pages;){
    double density = (double)r->tuples / (double)r->pages;
    s->ntup = clamp_row_est(density * (double)pages);
    break;
  }
  for(; NULL == r || r->tuples < 0 || r->pages <= 0;){
    int w =
      MAXALIGN(r->reltarget->width) + MAXALIGN(SizeofHeapTupleHeader);
    s->ntup = clamp_row_est((double) BLCKSZ * 10.0 / (double)w);
    break;
  }
  double nrow = s->ntup * clauselist_selectivity(
    p,
    r->baserestrictinfo,
    0,
    JOIN_INNER,
    NULL
  );
  return clamp_row_est(nrow);
}

static void dir_fdw_relsize(PlannerInfo* p, RelOptInfo* r, Oid o){
  DirFdwPlanState* s = palloc(sizeof(DirFdwPlanState));
  r->fdw_private = s;
  dir_fdw_options(o, &s->options);
  r->rows = dir_fdw_estimate(p, r, s);
  switch(NULL == s->options.dirname){
    case false: return;
    default:
      elog(ERROR, "invalid dirname.");
      return;
  }
}

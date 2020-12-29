#pragma once

#include <commands/explain.h>
#include <utils/rel.h>

#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>

static void dir_fdw_explain(ForeignScanState* f, ExplainState* e){
  DirFdwOption o = {0};
  dir_fdw_options(RelationGetRelid(f->ss.ss_currentRelation), &o);
  ExplainPropertyText("Foreign dirname", o.dirname, e);

  switch(!! e->costs){
    case false: return;
    default:    break;
  }

  struct stat s = {0};
  switch(stat(o.dirname, &s)){
    case -1: return;
    default: break;
  }
  ExplainPropertyInteger("Foreign dir size", "b", s.st_size, e);
}

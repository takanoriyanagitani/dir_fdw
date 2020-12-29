#pragma once

static void dir_fdw_begin(ForeignScanState* f, int eflags){
  switch(eflags & EXEC_FLAG_EXPLAIN_ONLY){
    case 0:  break;
    default: return;
  }

  DirFdwExecState* e = palloc(sizeof(DirFdwExecState));
  f->fdw_state = e;

  DirFdwOption o = {0};
  dir_fdw_options(RelationGetRelid(f->ss.ss_currentRelation), &o);
  switch(NULL==o.dirname){
    case false: break;
    default:
      elog(ERROR, "Invalid dirname.");
      return;
  }

  e->dirname = pstrdup(o.dirname);
  e->d = AllocateDir(e->dirname);
  switch(NULL == e->d){
    case false: return;
    default:    break;
  }
  elog(ERROR, "Unable to get fd.");
}

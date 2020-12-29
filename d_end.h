#pragma once

static void dir_fdw_end(ForeignScanState* f){
  DirFdwExecState* e = f->fdw_state;
  switch(FreeDir(e->d)){
    case 0:  return;
    default: break;
  }
  elog(WARNING, "Unable to free dir.");
}

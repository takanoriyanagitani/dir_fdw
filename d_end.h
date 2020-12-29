#pragma once

static void dir_fdw_end(ForeignScanState* f){
  for(DirFdwExecState* e = f->fdw_state; NULL != e;){
    for(DIR* d = e->d; NULL != d;){
      switch(FreeDir(e->d)){
        case 0:  return;
        default: break;
      }
      elog(WARNING, "Unable to free dir.");
      break;
    }
    break;
  }
}

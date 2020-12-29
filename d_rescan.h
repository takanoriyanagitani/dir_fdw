#pragma once

static void dir_fdw_rescan(ForeignScanState* f){
  DirFdwExecState* e = f->fdw_state;
  switch(NULL == e->d){
    case true: return;
    default:   break;
  }
  rewinddir(e->d);
}

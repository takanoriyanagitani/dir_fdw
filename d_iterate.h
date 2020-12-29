#pragma once

static Datum b2pgb8(const void* bytes){
  static const uint16_t bufsz = 256;
  int sz = bufsz + VARHDRSZ;
  bytea* ba = palloc(sz);
  memcpy(VARDATA(ba), bytes, bufsz);
  SET_VARSIZE(ba, sz);
  return PointerGetDatum(ba);
}

static TupleTableSlot* dir_fdw_iterate(ForeignScanState* f){
  DirFdwExecState* e = f->fdw_state;
  TupleTableSlot* s = f->ss.ss_ScanTupleSlot;

  TupleDesc t = s->tts_tupleDescriptor;
  int       n = t->natts;

  ExecClearTuple(s);

  switch(n){
    case 3: break;
    default:
      return s;
  }

  switch(NULL == e->dirname){
    case false: break;
    default:
      elog(ERROR, "invalid dirname.");
      return s;
  }

  struct dirent* d = ReadDir(e->d, e->dirname);
  switch(NULL == d){
    case true: return s;
    default:   break;
  }

  Datum* values = s->tts_values;
  bool*  nulls  = s->tts_isnull;

  values[0] = d->d_ino;
  values[1] = UInt8GetDatum(d->d_type);
  values[2] = b2pgb8(d->d_name);
  nulls[0] = false;
  nulls[1] = false;
  nulls[2] = false;
  ExecStoreVirtualTuple(s);

  return s;
}

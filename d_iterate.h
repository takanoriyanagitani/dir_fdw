#pragma once

const char* dtype_string(const u8n* u){
  static const char* f = "file";
  static const char* d = "directory";
  static const char* l = "link";
  static const char* n = "null";
  switch(u->is_null){
    case true: return n;
    default:   break;
  }
  switch(u->value){
    case DT_REG: return f;
    case DT_DIR: return d;
    case DT_LNK: return l;
    default:     return n;
  }
}

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

  nulls[0] = false; values[0] = d->d_ino;
  nulls[2] = false; values[2] = b2pgb8(d->d_name);
  nulls[1] = false; values[1] = d->d_type;
  ExecStoreVirtualTuple(s);

  return s;
}

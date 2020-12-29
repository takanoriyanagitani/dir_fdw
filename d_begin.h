#pragma once

#include <utils/builtins.h>

static bool op_is_eqs(const OpExpr* o){ return 67 == o->opfuncid; }

static void val2dtype(const char* val, u8n* dtype){
  for(; !!val;){
    switch(strnlen(val, 1)){
      case 0:  return;
      default: break;
    }
    switch(val[0]){
      case 'd': u8n_set(dtype, DT_DIR); return;
      case 'l': u8n_set(dtype, DT_LNK); return;
      case 'f': u8n_set(dtype, DT_REG); return;
      default:  return;
    }
    break;
  }
}

static void dir_fdw_set_filter(DirFdwExecState* s, const ScanState* ss){
  s->d_type = u8n_create();
  List* l = ss->ps.plan->qual;
  ListCell* i = NULL;
  TupleDesc td = ss->ss_currentRelation->rd_att;
  foreach(i, l){
    Expr* e = lfirst(i);
    for(Node* n=(Node*)e; n && IsA(n, OpExpr);){
      for(OpExpr* o=(OpExpr*)n; 2==list_length(o->args) && op_is_eqs(o);){
        for(Node* left=list_nth(o->args,0); IsA(left, Var);){
          for(Node* right=list_nth(o->args,1); IsA(right, Const);){
            Var* lv = (Var*)left;
            const char* col = NameStr(
              TupleDescAttr(td, lv->varattno-1)->attname
            );
            for(; 0 == strncmp(col, "d_type", 6);){
              Const* rc = (Const*)right;
              const char* val = TextDatumGetCString(rc->constvalue);
              val2dtype(val, &s->d_type);
              break;
            }
            break;
          }
          break;
        }
        break;
      }
      break;
    }
  }
}

static void dir_fdw_begin(ForeignScanState* f, int eflags){
  switch(eflags & EXEC_FLAG_EXPLAIN_ONLY){
    case 0:  break;
    default: return;
  }

  DirFdwExecState* e = palloc(sizeof(DirFdwExecState));
  f->fdw_state = e;
  dir_fdw_set_filter(e, &f->ss);

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

#pragma once

typedef struct u8n {
  uint8_t value;
  bool    is_null;
} u8n;

void u8n_foreach(const u8n* u, void* param, void cb(uint8_t,void*)){
  switch(u->is_null){
    case true: return;
    default:   break;
  }
  cb(u->value, param);
}

u8n u8n_create(){
  u8n u = {.value=0, .is_null=true};
  return u;
}

void u8n_set(u8n* u, const uint8_t v){
  u->value = v;
  u->is_null = false;
}

void u8n_datum(const u8n* u, Datum* v, bool* null){
  switch(u->is_null){
    case true: *null = true; break;
    default:
      *null = false;
      *v = UInt8GetDatum(u->value);
      break;
  }
}

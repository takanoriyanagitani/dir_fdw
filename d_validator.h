#pragma once

#include <postgres.h>

#include <foreign/fdwapi.h>

Datum dir_fdw_validator(PG_FUNCTION_ARGS){
  PG_RETURN_VOID();
}

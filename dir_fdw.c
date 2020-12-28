#include <postgres.h>
#include <funcapi.h>

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(dir_fdw_handler);
PG_FUNCTION_INFO_V1(dir_fdw_validator);

#include "d_validator.h"
#include "d_handler.h"

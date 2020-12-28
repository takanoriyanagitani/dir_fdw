\echo Use "CREATE EXTENSION dir_fdw" to load this file. \quit

CREATE FUNCTION dir_fdw_handler()
RETURNS fdw_handler
AS 'MODULE_PATHNAME'
LANGUAGE C STRICT;

CREATE FUNCTION dir_fdw_validator(text[], oid)
RETURNS void
AS 'MODULE_PATHNAME'
LANGUAGE C STRICT;

CREATE FOREIGN DATA WRAPPER dir_fdw
  HANDLER dir_fdw_handler
  VALIDATOR dir_fdw_validator;

CREATE EXTENSION     IF NOT EXISTS dir_fdw;
CREATE SERVER        IF NOT EXISTS dsv FOREIGN DATA WRAPPER dir_fdw;

CREATE FOREIGN TABLE IF NOT EXISTS dt(
  d_ino    BIGINT,
  d_type   CHAR,
  d_name   bytea,
  d_mode   BIGINT,
  d_nlink  INTEGER,
  d_user   BIGINT,
  d_group  BIGINT,
  d_size   BIGINT,
  d_bsize  BIGINT,
  d_bcnt   BIGINT
) SERVER dsv;

--SELECT * FROM dt WHERE k='hw';

DROP FOREIGN TABLE dt;
DROP SERVER        dsv;
DROP EXTENSION     dir_fdw;

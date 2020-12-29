#pragma once

typedef struct DirFdwPlanState {
  DirFdwOption options;

  BlockNumber pages;
  double      ntup;
} DirFdwPlanState;

typedef struct DirFdwExecState {
  const char* dirname;
  int fd;
  DIR* d;

  u8n d_type;
} DirFdwExecState;

/* xy_chain.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "def.h"
#include "pairs_find.h"
#include "xy_chain.h"

int xy_chain() {
#ifdef LOG_IN_OUT
  printf("--- xy_chain >>>\n");
#endif
  int result = pairs_find(DEF_XY_CHAIN);
#ifdef LOG_IN_OUT
  printf("<<< xy_chain ---\n");
#endif
  return result;
  }

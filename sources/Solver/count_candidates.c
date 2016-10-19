/* count_candidates.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "count_candidates.h"
#include "def.h"

int count_candidates() {
#ifdef LOG_IN_OUT
  printf("--- count_candidates >>>\n");
#endif
  int result = 0;
  for (int k = 0; k < 9; k++) {
    for (int j = 0; j < 9; j++) {
      result += grid[k][j][0];
      }
    }
#ifdef LOG_IN_OUT
  printf("<<< count_candidates ---\n");
#endif
  return result;
  }

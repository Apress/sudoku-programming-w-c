/* remove_candidate.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "def.h"
#include "remove_candidate.h"

void remove_candidate(char *caller, int i, int k, int j) {
  grid[k][j][i] = FALSE;
  grid[k][j][0]--;
#ifdef LOG_REMOVE_CANDIDATE
  if (!silent) {
    printf("%s: removed %d from (%d,%d)\n", caller, i, k, j);
    }
#endif
  if (grid[k][j][0] < 1) {
    if (!silent) {
      printf("*** No candidates left in (%d,%d)\n", k, j);
      }
    problem_found = TRUE;
    }
  }

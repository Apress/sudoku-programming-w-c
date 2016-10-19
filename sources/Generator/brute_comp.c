/* brute_comp.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "brute.h"
#include "brute_comp.h"
#include "def.h"
#include "inconsistent_grid.h"

// This messages in clear must match the codes defined in brute_comp.h
const char *brute_comp_err[] = {
    /* 0 */ "same as reference",
    /* 1 */ "different from reference",
    /* 2 */ "timeout",
    /* 3 */ "grid inconsistent",
    /* 4 */ "puzzle impossible",
    /* 5 */ "unknown result"
    };

int brute_comp() {
  int result = BRUTE_COMP_PROBLEM;
  int brute_result = brute();
  switch (brute_result) {

    case BRUTE_SUCCESSFUL:
      result = BRUTE_COMP_OK;
      for (int kk = 0; kk < 9 && result == BRUTE_COMP_OK; kk++) {
        for (int jj = 0; jj < 9 && result == BRUTE_COMP_OK; jj++) {
          if (solved[kk][jj] != grid[kk][jj]) result = BRUTE_COMP_DIFFERENT;
          }
        }
      if (inconsistent_grid()) result = BRUTE_COMP_INCONSISTENT;
      break;

    case BRUTE_IMPOSSIBLE:
      result = BRUTE_COMP_IMPOSSIBLE;
      break;

    case BRUTE_TIMEOUT:
      result = BRUTE_COMP_TIMEOUT;
      break;

    default:
      result = BRUTE_COMP_PROBLEM;
      break;
    }
  return result;
  }

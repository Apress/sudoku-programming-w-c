/* count_solved.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "count_solved.h"
#include "def.h"

int count_solved() {
  int result = 0;
  for (int k = 0; k < 9; k++) {
    for (int j = 0; j < 9; j++) {
      if (grid[k][j] != 0) result++;
      }
    }
  return result;
  }

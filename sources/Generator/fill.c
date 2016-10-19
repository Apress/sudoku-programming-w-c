/* fill.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "def.h"
#include "display.h"
#include "fill.h"
#include "fill_digit.h"

int fill(void) {
  int problem_found = FALSE;
  int i;
  int kkount = 0;
  for (i = 1; i <= 9 && kkount < 729; i++) {
    int kount = 0;
    do {
      kount++;
      problem_found = fill_digit((char)i);
      if (!silent) printf("fill %d [%d %d]: %s\n",
          i, kount, kkount, (problem_found) ? "failed" : "succeeded"
          );
      } while (problem_found && kount < 9);

    if (problem_found) {
      for (int k = 0; k < 9; k++) {
        for (int j = 0; j < 9; j++) {
          if (grid[k][j] == i || grid[k][j] == i-1) grid[k][j] = 0;
          }
        }
      i -= 2;
      } // if (problem_found..
    kkount++;
    }
  return problem_found || kkount >= 729;
  }

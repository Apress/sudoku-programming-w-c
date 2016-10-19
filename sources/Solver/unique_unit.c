/* unique_unit.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "cleanup_around.h"
#include "def.h"
#include "remove_candidate.h"
#include "unique_unit.h"

int unique_unit(char *what, char unit[9][2]) {
#ifdef LOG_IN_OUT
  printf("--- unique_unit (%s) >>>\n", what);
#endif
  int result = FALSE;
  int r[10]; for (int i = 0; i < 10; i++) { r[i] = -1; }
  int c[10];
  for (int j1 = 0; j1 < 9; j1++) {
    int kR = unit[j1][0];
    int kC = unit[j1][1];
    char *elem = grid[kR][kC];
    if (elem[0] > 1) {
      for (int i = 1; i <= 9; i++) {
        if (elem[i] != FALSE) {
          if (r[i] == -1) {
            r[i] = kR;
            c[i] = kC;
            }
          else {
            r[i] = -2;
            }
          } // if (elem[i]..
        } // for (int i..
      } // if (elem[0]..
    } // for (int j1..

  for (int i = 1; i <= 9 && !problem_found; i++) {
    if (r[i] >= 0) {
      result = TRUE;
      int kR = r[i];
      int kC = c[i];
#ifdef LOG_UNIQUE
      if (!silent) {
        printf("unique_unit: %d in (%d,%d) is unique within the %s\n",
            i, kR, kC, what
            );
        }
#endif
      char *elem = grid[kR][kC];
      for (int ii = 1; ii <= 9 && !problem_found; ii++) {
        if (elem[ii] != FALSE && i != ii) {
          remove_candidate("unique_unit", ii, kR, kC);
          }
        }
      if (!problem_found) cleanup_around(kR, kC);
      } // if (r[i]..
    } // for int i..

#ifdef LOG_IN_OUT
  printf("<<< unique_unit (%s) ---\n", what);
#endif
  return result;
  }

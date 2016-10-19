/* inconsistent_unit.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "def.h"
#include "inconsistent_unit.h"

int inconsistent_unit(char *what, int kG, char unit[9][2]) {
  int result = FALSE;
  int i_vect[10] = {0};
  for (int k = 0; k < 9 && !result; k++) {
    int kR = unit[k][ROW];
    int kC = unit[k][COL];
    char *elem = grid[kR][kC];
    if (elem[0] < 1) {  // we have an empty cell
      result = TRUE;
      if (!silent) {
        printf("*** (%d,%d) has %d candidates\n", kR, kC, elem[0]);
        }
      } // if (elem[0]..
    else if (elem[0] == 1) {
      int i = 0;
      do { i++; } while (!elem[i]);
      if (i_vect[i] == FALSE) {
        i_vect[i] = TRUE;
        }
      else {  // we have a duplicate solution
        result = TRUE;
        if (!silent) {
          printf("*** More than a single %d solution in %s %d\n", i, what, kG);
          }
        } // else..
      } // else if (elem[0]..
    } // for (int k..
  problem_found = result;
  return result;
  }

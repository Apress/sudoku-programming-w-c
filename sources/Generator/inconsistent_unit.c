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
    int i = grid[kR][kC];
    if (i > 0) {
      if (i_vect[i] == FALSE) {
        i_vect[i] = TRUE;
        }
      else {  // we have a duplicate solution
        result = TRUE;
        }
      } // if (i..
    } // for (int k..
  return result;
  }

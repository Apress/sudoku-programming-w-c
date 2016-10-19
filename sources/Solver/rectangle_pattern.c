/* rectangle_pattern.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "def.h"
#include "rectangle_cell.h"
#include "rectangle_pattern.h"

int rectangle_pattern(int pattern[4]) {
#ifdef LOG_IN_OUT
  printf("--- rectangle_pattern (");
  for (int k = 0; k < 4; k++) {
    if (k > 0) printf(",");
    printf("%d", pattern[k]);
    }
  printf(") >>>\n");
#endif
  int result = FALSE;
  int cells = TRUE;
  for (int kB = 0; kB < 4 && cells; kB++) {
    cells = FALSE;
    int sID = pattern[kB];
    for (int kE = 0; kE < 9 && !cells; kE++) {
      int kR = box[sID][kE][ROW];
      int kC = box[sID][kE][COL];
      if (grid[kR][kC][0] > 1) cells = TRUE;
      }
    }

  if (cells) {
    for (int kB = 0; kB < 4  &&  !result; kB++) {
      int seq[4];
      for (int k = 0; k < 4; k++) {
        int kk = (kB + k) % 4;
        seq[k] = pattern[kk];
        }
      int sID = seq[0];
      for (int kE = 0; kE < 9  &&  !result; kE++) {
        int kR = box[sID][kE][ROW];
        int kC = box[sID][kE][COL];
        if (grid[kR][kC][0] > 1) result = rectangle_cell(seq, kR, kC);
        } // for (int kE..
      } // for (int kB..
    } // if (cells..

#ifdef LOG_IN_OUT
  printf("<<< rectangle_pattern (");
  for (int k = 0; k < 4; k++) {
    if (k > 0) printf(",");
    printf("%d", pattern[k]);
    }
  printf(") ---\n");
#endif
  return result;
  }

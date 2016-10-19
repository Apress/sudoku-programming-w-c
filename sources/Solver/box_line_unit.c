/* box_line_unit.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "box_line_unit.h"
#include "cleanup_around.h"
#include "def.h"
#include "remove_candidate.h"

int box_line_unit(int row_col, char line[9][2]) {
#ifdef LOG_IN_OUT
  printf("--- box_line_unit (%s) >>>\n", unit_names[row_col]);
#endif
  int result = FALSE;
  int b[10]; for (int i = 0; i < 10; i++) { b[i] = -1; }
  int rc[10];
  for (int j1 = 0; j1 < 9; j1++) {
    int kR = line[j1][ROW];
    int kC = line[j1][COL];
    char *elem = grid[kR][kC];
    if (elem[0] > 1) {
      for (int i = 1; i <= 9; i++) {
        if (elem[i] != FALSE) {
          int kB = kR/3*3 + kC/3;
          if (b[i] == -1) {
            b[i] = kB;
            rc[i] = (row_col == ROW) ? kR : kC;
            }
          else if (b[i] != kB) {
            b[i] = -2;
            }
          } // if (elem[i]..
        } // for (int i..
      } // if (elem[0]..
    } // for (int j1..

  for (int i = 1; i <= 9; i++) {
    if (b[i] >= 0) {
      int log_printed = FALSE;
      int kB = b[i];
      int kL = rc[i];
      for (int kE = 0; kE < 9; kE++) {
        int kR = box[kB][kE][ROW];
        int kC = box[kB][kE][COL];
        int kRC = (row_col == ROW) ? kR : kC;
        if (kRC != kL) {
          char *elem = grid[kR][kC];
          if (elem[i] != FALSE) {
            result = TRUE;
#ifdef LOG_BOX_LINE
            if (!log_printed && !silent) {
              printf("box_line_unit: all candidates for %d of %s %d"
                  " are in box %d\n", i, unit_names[row_col], kL, kB
                  );
              log_printed = TRUE;
              }
#endif
            remove_candidate("box_line_unit", i, kR, kC);
            if (grid[kR][kC][0] == 1) {
              cleanup_around(kR, kC);
              }
            } // if (elem[i]..
          } // if (kRC..
        } // for (int kE..
      } // if (b[i]..
    } // for (int i..

#ifdef LOG_IN_OUT
  printf("<<< box_line_unit (%s) ---\n", unit_names[row_col]);
#endif
  return result;
  }

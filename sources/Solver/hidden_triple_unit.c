/* hidden_triple_unit.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "def.h"
#include "hidden_triple_unit.h"
#include "remove_candidate.h"

int hidden_triple_unit(char *what, char unit[9][2]) {
#ifdef LOG_IN_OUT
  printf("--- hidden_triple_unit (%s) >>>\n", what);
#endif
  int result = FALSE;
  int n[10] = {0};
  int coords[10][3][2];
  for (int j1 = 0; j1 < 9; j1++) {
    int kR = unit[j1][ROW];
    int kC = unit[j1][COL];
    char *elem = grid[kR][kC];
    if (elem[0] > 1) {
      for (int i = 1; i <= 9; i++) {
        if (elem[i] != FALSE) {
          if (n[i] < 3) {
            coords[i][n[i]][ROW] = kR;
            coords[i][n[i]][COL] = kC;
            }
          n[i]++;
          } // if (elem[i]..
        } // for (int i..
      } // if (elem[0]..
    } // for (int j1..

  for (int i1 = 1; i1 <= 9; i1++) {
    if (n[i1] == 3) {
      int log_printed = FALSE;
      for (int i2 = i1+1; i2 <= 9; i2++) {
        if (    n[i2] == 3
             && coords[i1][0][ROW] == coords[i2][0][ROW]
             && coords[i1][0][COL] == coords[i2][0][COL]
             && coords[i1][1][ROW] == coords[i2][1][ROW]
             && coords[i1][1][COL] == coords[i2][1][COL]
             && coords[i1][2][ROW] == coords[i2][2][ROW]
             && coords[i1][2][COL] == coords[i2][2][COL]
             ) {
          for (int i3 = i2+1; i3 <= 9; i3++) {
            if (    n[i3] == 3
                 && coords[i1][0][ROW] == coords[i3][0][ROW]
                 && coords[i1][0][COL] == coords[i3][0][COL]
                 && coords[i1][1][ROW] == coords[i3][1][ROW]
                 && coords[i1][1][COL] == coords[i3][1][COL]
                 && coords[i1][2][ROW] == coords[i3][2][ROW]
                 && coords[i1][2][COL] == coords[i3][2][COL]
                 ) {
              for (int kCell = 0; kCell < 3; kCell++) {
                int kRow = coords[i1][kCell][ROW];
                int kCol = coords[i1][kCell][COL];
                char *elem = grid[kRow][kCol];
                if (elem[0] > 3) {
                  result = TRUE;
#ifdef LOG_HIDDEN_TRIPLE
                  if (log_printed == FALSE && !silent) {
                    printf("hidden_triple_unit: %d, %d, and %d are only in "
                        "(%d,%d), (%d,%d), and (%d,%d) of the same %s\n",
                        i1, i2, i3, coords[i1][0][0], coords[i1][0][1],
                        coords[i1][1][0], coords[i1][1][1],
                        coords[i1][2][0], coords[i1][2][1], what
                        );
                    log_printed = TRUE;
                    }
#endif
                  for (int ki = 1; ki <= 9; ki++) {
                    if (elem[ki] && ki != i1 && ki != i2 && ki != i3) {
                      remove_candidate("hidden_triple_unit", ki, kRow, kCol);
                      }
                    }
                  } // if (elem[0]..
                } // for (int kCell..
              } // if (n[i3]..
            } // for (int i3..
          } // if (n[i2]..
        } // for (int i2..
      } // if (n[i1]..
    } // for (int i1..

#ifdef LOG_IN_OUT
  printf("<<< hidden_triple_unit (%s) ---\n", what);
#endif
  return result;
  }

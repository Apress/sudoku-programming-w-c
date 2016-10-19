/* hidden_pair_unit.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "cleanup_around.h"
#include "def.h"
#include "hidden_pair_unit.h"
#include "remove_candidate.h"

int hidden_pair_unit(char *what, char unit[9][2]) {
#ifdef LOG_IN_OUT
  printf("--- hidden_pair_unit (%s) >>>\n", what);
#endif
  int result = FALSE;
  int n[10] = {0};
  int coords[10][2][2];
  for (int j1 = 0; j1 < 9; j1++) {
    int kR = unit[j1][ROW];
    int kC = unit[j1][COL];
    char *elem = grid[kR][kC];
    if (elem[0] > 1) {
      for (int i = 1; i <= 9; i++) {
        if (elem[i] != FALSE) {
          if (n[i] < 2) {
            coords[i][n[i]][ROW] = kR;
            coords[i][n[i]][COL] = kC;
            }
          n[i]++;
          } // if (elem[i]..
        } // for (int i..
      } // if (elem[0]..
    } // for (int j1..

  for (int i = 1; i <= 9; i++) {
    if (n[i] == 2) {
      int log_printed = FALSE;
      for (int ii = i+1; ii <= 9; ii++) {
        if (n[ii] == 2
            && coords[i][0][ROW] == coords[ii][0][ROW]
            && coords[i][0][COL] == coords[ii][0][COL]
            && coords[i][1][ROW] == coords[ii][1][ROW]
            && coords[i][1][COL] == coords[ii][1][COL]
            ) {
          for (int kCell = 0; kCell < 2; kCell++) {
            int kR = coords[i][kCell][ROW];
            int kC = coords[i][kCell][COL];
            char *elem = grid[kR][kC];
            if (elem[0] > 2) {
              result = TRUE;
#ifdef LOG_HIDDEN_PAIR
              if (log_printed == FALSE && !silent) {
                printf("hidden_pair_unit: %d and %d are only in (%d,%d) and (%d,%d) of the same %s\n",
                    i, ii, coords[i][0][0], coords[i][0][1], coords[i][1][0], coords[i][1][1], what
                    );
                log_printed = TRUE;
                }
#endif
              for (int iii = 1; iii <= 9; iii++) {
                if (elem[iii] != FALSE && i != iii && ii != iii) {
                  remove_candidate("hidden_pair_unit", iii, kR, kC);
                  }
                }
              } // if (elem[0]..
            } // for (int kCell..
          } // if (n[ii]..
        } // for (int ii..
      } // if (n[i]..
    } // for (int i..

#ifdef LOG_IN_OUT
  printf("<<< hidden_pair_unit (%s) ---\n", what);
#endif
  return result;
  }

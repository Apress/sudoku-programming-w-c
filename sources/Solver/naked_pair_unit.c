/* naked_pair_unit.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "cleanup_around.h"
#include "def.h"
#include "naked_pair_unit.h"
#include "remove_candidate.h"

int naked_pair_unit(char *what, char unit[9][2]) {
#ifdef LOG_IN_OUT
  printf("--- naked_pair_unit (%s) >>>\n", what);
#endif
  int result = FALSE;
  int i1[9] = {0};
  int i2[9] = {0};
  int kRow[9] = {0};
  int kCol[9] = {0};
  int kk[9] = {0};
  int n_pair = 0;

  // Make a list of the cells with naked pairs.
  for (int k = 0; k < 9; k++) {
    int kR = unit[k][0];
    int kC = unit[k][1];
    char *elem = grid[kR][kC];
    if (elem[0] == 2) {
      kRow[n_pair] = kR;
      kCol[n_pair] = kC;
      kk[n_pair] = k;
      for (int i = 1; i <= 9 && i2[n_pair] == 0; i++) {
        if (elem[i] == TRUE) {
          if (i1[n_pair] == 0) {
            i1[n_pair] = i;
            }
          else {
            i2[n_pair] = i;
            }
          } // if (elem[i]..
        } // for (int i..
      n_pair++;
      } // if (elem[0]..
    } // for (int k..

  if (n_pair > 1) {
    for (int k1 = 0; k1 < n_pair - 1; k1++) {
      for (int k2 = k1 + 1; k2 < n_pair; k2++) {
        if (i1[k1] == i1[k2] && i2[k1] == i2[k2]) {
          int printed = FALSE;
          for (int k = 0; k < 9; k++) {
            if (k != kk[k1] && k != kk[k2]) {
              int kR = unit[k][0];
              int kC = unit[k][1];
              char *elem = grid[kR][kC];
              int i_remove[2];
              int n_remove = 0;
              if (elem[i1[k1]] == TRUE) {
                i_remove[n_remove] = i1[k1];
                n_remove++;
                result = TRUE;
                }
              if (elem[i2[k1]] == TRUE) {
                i_remove[n_remove] = i2[k1];
                n_remove++;
                result = TRUE;
                }
#ifdef LOG_NAKED_PAIR
              if (n_remove > 0 && !printed && !silent) {
                printf("naked_pair_unit: (%d,%d) and (%d,%d) in the same %s"
                    " only contain %d and %d\n", kRow[k1], kCol[k1], kRow[k2],
                    kCol[k2], what, i1[k1], i2[k1]
                    );
                printed = TRUE;
                }
#endif
              for (int ki = 0; ki < n_remove; ki++) {
                remove_candidate("naked_pair_unit", i_remove[ki], kR, kC);
                if (grid[kR][kC][0] == 1) {
                  cleanup_around(kR, kC);
                  }
                }
              } // if (k..
            } // for (int k..
          } // if (i1[k1]..
        } // for (int k2..
      } // for (int k1..
    } // if (n_pair..

#ifdef LOG_IN_OUT
  printf("<<< naked_pair_unit (%s) ---\n", what);
#endif
  return result;
  }

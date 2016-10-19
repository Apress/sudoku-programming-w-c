/* naked_quad_unit.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "cleanup_around.h"
#include "def.h"
#include "naked_quad_unit.h"
#include "remove_candidate.h"

int naked_quad_unit(char *what, char unit[9][2]) {
#ifdef LOG_IN_OUT
  printf("--- naked_quad_unit (%s) >>>\n", what);
#endif
  int result = FALSE;
  int i1[9] = {0};
  int i2[9] = {0};
  int i3[9] = {0};
  int i4[9] = {0};
  int kRow[9] = {0};
  int kCol[9] = {0};
  int kk[9] = {0};
  int n_quad = 0;

  // Make a list of the cells with naked quads.
  for (int k = 0; k < 9; k++) {
    int kR = unit[k][0];
    int kC = unit[k][1];
    char *elem = grid[kR][kC];
    if (elem[0] == 4) {
      kRow[n_quad] = kR;
      kCol[n_quad] = kC;
      kk[n_quad] = k;
      for (int i = 1; i <= 9 && i4[n_quad] == 0; i++) {
        if (elem[i] == TRUE) {
          if (i1[n_quad] == 0) {
            i1[n_quad] = i;
            }
          else if (i2[n_quad] == 0) {
            i2[n_quad] = i;
            }
          else if (i3[n_quad] == 0) {
            i3[n_quad] = i;
            }
          else {
            i4[n_quad] = i;
            }
          } // if (elem[i]..
        } // for (int i..
      n_quad++;
      } // if (elem[0]..
    } // for (int k..

  if (n_quad > 3) {
    for (int k1 = 0; k1 < n_quad - 3; k1++) {
      for (int k2 = k1 + 1; k2 < n_quad - 2; k2++) {
        for (int k3 = k2 + 1; k3 < n_quad - 1; k3++) {
          for (int k4 = k3 + 1; k4 < n_quad; k4++) {
            if (    i1[k1] == i1[k2] && i1[k1] == i1[k3] && i1[k1] == i1[k4]
                 && i2[k1] == i2[k2] && i2[k1] == i2[k3] && i2[k1] == i2[k4]
                 && i3[k1] == i3[k2] && i3[k1] == i3[k3] && i3[k1] == i3[k4]
                 && i4[k1] == i4[k2] && i4[k1] == i4[k3] && i4[k1] == i4[k4]
                 ) {
              int printed = FALSE;
              for (int k = 0; k < 9; k++) {
                if (k != kk[k1] && k != kk[k2] && k != kk[k3] && k != kk[k4]) {
                  int kR = unit[k][0];
                  int kC = unit[k][1];
                  char *elem = grid[kR][kC];
                  int i_remove[4];
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
                  if (elem[i3[k1]] == TRUE) {
                    i_remove[n_remove] = i3[k1];
                    n_remove++;
                    result = TRUE;
                    }
                  if (elem[i4[k1]] == TRUE) {
                    i_remove[n_remove] = i4[k1];
                    n_remove++;
                    result = TRUE;
                    }
#ifdef LOG_NAKED_QUAD
                  if (n_remove > 0 && !printed && !silent) {
                    printf("naked_quad_unit: (%d,%d), (%d,%d), (%d,%d),"
                        " and (%d,%d)"
                        " in the same %s only contain %d, %d, %d, and %d\n",
                        kRow[k1], kCol[k1], kRow[k2], kCol[k2], kRow[k3],
                        kCol[k3], kRow[k4], kCol[k4], what, i1[k1], i2[k1],
                        i3[k1], i4[k1]
                        );
                    printed = TRUE;
                    }
#endif
                  for (int ki = 0; ki < n_remove; ki++) {
                    remove_candidate("naked_quad_unit", i_remove[ki], kR, kC);
                    if (grid[kR][kC][0] == 1) {
                      cleanup_around(kR, kC);
                      }
                    }
                  } // if (k..
                } // for (int k..
              } // if (i1[k1]..
            } // for (int k4..
          } // for (int k3..
        } // for (int k2..
      } // for (int k1..
    } // if (n_quad..

#ifdef LOG_IN_OUT
  printf("<<< naked_quad_unit (%s) ---\n", what);
#endif
  return result;
  }

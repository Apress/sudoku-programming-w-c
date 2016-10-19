/* lines.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cleanup_around.h"
#include "def.h"
#include "lines.h"
#include "remove_candidate.h"

int lines(int kRC, char *comb, int n, int i) {
#ifdef LOG_IN_OUT
  printf("--- lines (%s) [", unit_names[kRC]);
  for (int k = 0; k < n; k++) printf("%d", comb[k]);
  printf("] %d >>>\n", i);
#endif
  int result = FALSE;
  int list[9] = {0};
  int n_list = 0;
  int abort = FALSE;
  for (int k = 0; k < n && !abort; k++) {
    int kk[2];
    kk[0] = comb[k];
    for (int j = 0; j < 9 && !abort; j++) {
      kk[1] = j;
      int kR = kk[kRC];
      int kC = kk[1-kRC];
      char *elem = grid[kR][kC];
      if (elem[i]) {
        if (elem[0] == 1) {
          abort = TRUE;
          }
        else {
          if (!list[j]) n_list++;
          list[j] = TRUE;
          }
        } // if (elem[i]..
      } // for (int j..
    } // for (int k..

  if (!abort && n_list == n) {
    int log_printed = FALSE;
    for (int jj = 0; jj < 9; jj++) {
      if (list[jj]) {
        int kk[2];
        kk[1] = jj;
        for (int k = 0; k < 9; k++) {
          if (memchr(comb, k, n) == NULL) {
            kk[0] = k;
            int kR = kk[kRC];
            int kC = kk[1-kRC];
            char *elem = grid[kR][kC];

            // As usual, we assume that the Sudoku is not corrupted. It means
            // that 'i' doesn't solve any of the cells we are considering.
            // Otherwise, the candidate for 'i' would have already been removed
            // from the row, and the column ID would have not been saved in list.
            if (elem[i]) {
              result = TRUE;
#ifdef LOG_LINES
              if (!log_printed && !silent) {
                printf("lines(%d): the %ss", n, unit_names[kRC]);
                for (int k1 = 0; k1 < n; k1++) printf(" %d", comb[k1]);
                printf(" let us eliminate %d from the %ss", i,
                    unit_names[1-kRC]
                    );
                for (int k1 = 0; k1 < 9; k1++) {
                  if (list[k1]) printf(" %d", k1);
                  }
                printf("\n");
                log_printed = TRUE;
                }
#endif
              remove_candidate("lines", i, kR, kC);
              if (grid[kR][kC][0] == 1) {
                cleanup_around(kR, kC);
                }
              } // if (elem[i]..
            } // if (memchr(..
          } // for (int k..
        } // if (list[jj]..
      } // for (int jj..
    } // if (!abort..
#ifdef LOG_IN_OUT
  printf("<<< lines (%s) [", unit_names[kRC]);
  for (int k = 0; k < n; k++) printf("%d", comb[k]);
  printf("] %d ---\n", i);
#endif
  return result;
  }

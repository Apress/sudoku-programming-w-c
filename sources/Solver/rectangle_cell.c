/* rectangle_cell.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "cleanup_around.h"
#include "def.h"
#include "rectangle_cell.h"
#include "rectangle_step.h"
#include "remove_candidate.h"

int rectangle_cell(int seq[4], int kR, int kC) {
#ifdef LOG_IN_OUT
  printf("--- rectangle_cell [");
  for (int k = 0; k < 4; k++) {
    if (k > 0) printf(",");
    printf("%d", seq[k]);
    }
  printf("] (%d,%d) >>>\n", kR, kC);
#endif
  int result = FALSE;

  char *elem = grid[kR][kC];
  for (int i = 1; i <= 9  &&  !result; i++) {
    if (elem[i]) {
      int res = rectangle_step(seq, 0, kR, kC, i, kR, kC);
      if (res == 0) {
#ifdef LOG_RECTANGLE
        if (!silent) {
          printf("rectangle_cell: %d in (%d,%d) leads to contradiction"
              " when chained through the boxes [%d,%d,%d,%d]\n",
              i, kR, kC, seq[0], seq[1], seq[2], seq[3]
              );
          }
#endif
        remove_candidate("rectangle_cell", i, kR, kC);
        if (grid[kR][kC][0] == 1) {
          cleanup_around(kR, kC);
          }
        result = TRUE;
        } // if (res..
      else if (res == -2) {
        result = TRUE;
        }
      } // if (elem[i]..
    } // for (int i..

#ifdef LOG_IN_OUT
  printf("<<< rectangle_cell [");
  for (int k = 0; k < 4; k++) {
    if (k > 0) printf(",");
    printf("%d", seq[k]);
    }
  printf("] (%d,%d) ---\n", kR, kC);
#endif
  return result;
  }

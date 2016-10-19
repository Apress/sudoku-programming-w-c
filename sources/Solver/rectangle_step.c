/* rectangle_step.c
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

int rectangle_step(int seq[4], int kBeq, int kR, int kC, int kN,
        int iR, int iC
        ) {
#ifdef LOG_IN_OUT
  printf("--- rectangle_step [");
  for (int k = kBeq; k < 4; k++) {
    printf("%d", seq[k]);
    if (k < 3) printf(",");
    }
  printf("] (%d,%d) %d >>>\n", kR, kC, kN);
#endif
  int result = 0;
  int kB = seq[kBeq+1];
  if (kBeq == 3) kB = seq[0];
  int n = 0;
  int rows[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  int cols[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  for (int kE = 0; kE < 9 && result >= 0; kE++) {
    int kkR = box[kB][kE][0];
    int kkC = box[kB][kE][1];
    char *elem = grid[kkR][kkC];
    if (elem[0] == 1) {
      if (elem[kN] != FALSE) {
        result = -1;
        }
      } // if (elem[0]..
    else if (elem[kN] != FALSE && kkR != kR && kkC != kC) {
      rows[n] = kkR;
      cols[n] = kkC;
      n++;
      } // if (elem[0].. else..
    } // for (int kE..

  if (n > 0 || kBeq == 3) {
    if (kBeq < 3) {
      for (int k = 0; k < n && result >= 0; k++) {
        int res = rectangle_step(seq, kBeq+1, rows[k], cols[k], kN, iR, iC);
        if (res < 0) {
          result = res;
          }
        else {
          result |= res;
          }
        } // for (int k..
      } // if (kBeq..
    else {
      for (int k = 0; k < n && result == 0; k++) {
        if (rows[k] == iR && cols[k] == iC) {
          result = 1;
          }
        } // for (int k..
      } // if (kBeq.. else..
    } // if (n > 0..
  else if (n == 0 && result != -1) {  // the pointing-line strategy applies
    result = -2;
#ifdef LOG_POINTING_LINE
    if (!silent) {
      printf("rectangle_step: %d cannot solve (%d,%d) because all the %ds "
          "in box %d are aligned with it (pointing-line strategy)\n",
          kN, kR, kC, kN, kB
          );
      }
#endif
    remove_candidate("rectangle_step", kN, kR, kC);
    if (grid[kR][kC][0] == 1) {
      cleanup_around(kR, kC);
      }
    } // if (n > 0.. else if (n..

#ifdef LOG_IN_OUT
  printf("<<< rectangle_step [");
  for (int k = kBeq; k < 4; k++) {
    printf("%d", seq[k]);
    if (k < 3) printf(",");
    }
  printf("] (%d,%d) %d return=%d ---\n", kR, kC, kN, result);
#endif
  return result;
  }

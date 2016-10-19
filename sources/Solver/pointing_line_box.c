/* pointing_line_box.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "cleanup_around.h"
#include "def.h"
#include "pointing_line_box.h"
#include "remove_candidate.h"

int pointing_line_box(int boxid, char box[9][2]) {
#ifdef LOG_IN_OUT
  printf("--- pointing_line_box >>>\n");
#endif
  int result = FALSE;
  int rc[10][2];
  for (int i = 0; i < 10; i++) {
    for (int k = 0; k < 2; k++) {
      rc[i][k] = -1;
      }
    }
  for (int k = 0; k < 9; k++) {
    int kR = box[k][ROW];
    int kC = box[k][COL];
    char *elem = grid[kR][kC];
    if (elem[0] > 1) {
      for (int i = 1; i <= 9; i++) {
        if (elem[i]) {
          for (int krc = 0; krc < 2; krc++) {
            if (rc[i][krc] == -1) {
              rc[i][krc] = box[k][krc];
              }
            else if (box[k][krc] != rc[i][krc]) {
              rc[i][krc] = -2;
              }
            } // for (int krc..
          } // if (elem[i]..
        } // for (int i..
      } // if (elem[0]..
    } // for (int k..

  int log_printed = FALSE;
  int kRC[2] = {0};
  for (int i = 1; i <= 9; i++) {
    for (int krc = 0; krc < 2; krc++) {
      if (rc[i][krc] >= 0) {
        kRC[krc] = rc[i][krc];
        for (int kk = 0; kk < 9; kk++) {
          kRC[1-krc] = kk;
          int kR = kRC[ROW];
          int kC = kRC[COL];
          if (boxid != kR/3*3+kC/3) {
            char *elem = grid[kR][kC];
            if (elem[i]) {
              result = TRUE;
#ifdef LOG_POINTING_LINE
              if (!log_printed && !silent) {
                printf("pointing_line_box: all candidates for %d"
                    " of box %d are in ", i, boxid
                    );
                if (krc == ROW) {
                  printf("row %d\n", kR);
                  }
                else {
                  printf("column %d\n", kC);
                  }
                log_printed = TRUE;
                }
#endif
              remove_candidate("pointing_line_box", i, kR, kC);
              if (grid[kR][kC][0] == 1) {
                cleanup_around(kR, kC);
                }
              } // if (elem[i]..
            } // if (boxid..
          } // for (int kk..
        } // if (rc[i][k]..
      } // for (int k..
    } // for (int i..

#ifdef LOG_IN_OUT
  printf("<<< pointing_line_box ---\n");
#endif
  return result;
  }

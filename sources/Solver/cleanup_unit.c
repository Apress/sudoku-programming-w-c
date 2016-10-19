/* cleanup_unit.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "cleanup_around.h"
#include "cleanup_unit.h"
#include "def.h"
#include "remove_candidate.h"

void cleanup_unit(char *what, int kElem, int jElem, char unit[9][2]) {
#ifdef LOG_IN_OUT
  printf("--- cleanup_unit (%s) for (%d,%d) >>>\n", what, kElem, jElem);
#endif
  char *elem = grid[kElem][jElem];
  if (elem[0] == 1) {
    int i = 0;
    do { i++; } while (elem[i] == FALSE);
    for (int j1 = 0; j1 < 9 && !problem_found; j1++) {
      int kR = unit[j1][ROW];
      int kC = unit[j1][COL];
      if ((kR != kElem || kC != jElem) && grid[kR][kC][i] != FALSE) {
        char mess[40];
        sprintf(mess, "cleanup_unit [%s of (%d,%d)]", what, kElem, jElem);
        remove_candidate(mess, i, kR, kC);
        if (grid[kR][kC][0] == 1 && !problem_found) {
          cleanup_around(kR, kC);
          }
        }
      }
    }
#ifdef LOG_IN_OUT
  printf("<<< cleanup_unit (%s) for (%d,%d) ---\n", what, kElem, jElem);
#endif
  }

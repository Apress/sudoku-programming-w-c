/* footprint.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "def.h"
#include "footprint.h"

rc_p_t footprint(int row, int col, void *mem) {
#ifdef LOG_IN_OUT
  printf("--- footprint >>>\n");
#endif

  rc_p_t rc = (rc_p_t)mem;
  int box = row/3*3+col/3;

  rc_p_t p = rc;
  rc_p_t next;
  for (int k = 0; k < 9; k++) {
    for (int j = 0; j < 9; j++) {
      if (k != row ||  j  != col) {
        if (k == row  ||  j == col  ||  k/3*3+j/3 == box) {
          p->row = k;
          p->col = j;
          next = p + 1;
          p->next = next;
          p = next;
          } // if (k == row..
        } // if (k..
      } // for (int j..
    } // for (int k..

  // Terminate the chain by clearing the 'next' pointer of the last cell
  p = rc + (FOOT_N - 1);
  p->next = NULL;

#ifdef LOG_IN_OUT
  printf("<<< footprint ---\n");
#endif
  return rc;
  }

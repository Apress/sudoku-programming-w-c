/* brute.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "brute.h"
#include "def.h"
#include "inconsistent_unit.h"

int brute() {
  int result = BRUTE_SUCCESSFUL;
  unsigned long start_time = clock()/CLOCKS_PER_SEC;
  unsigned long this_time;
  char initial[9][9];
  for (int k = 0; k < 9; k++) {
    for (int j = 0; j < 9; j++) {
      initial[k][j] = grid[k][j];
      }
    }
  int k = 0;
  int j = 0;
  do {
    do {
      if (initial[k][j] == 0) {
        int i = grid[k][j] + 1;
        if (i > 9) {
          grid[k][j] = 0;
          do {
            do { j--; } while (j >= 0 && initial[k][j] != 0);
            if (j < 0) {
              k--;
              if (k < 0) {
                result = BRUTE_IMPOSSIBLE;
                goto done;                                                //==>
                }
              j = 8;
              }
            } while (initial[k][j] != 0);
          } // if (i..
        else {
          grid[k][j] = i;
          int kB = k/3*3+j/3;
          if (    !inconsistent_unit("row", k, row[k])
               && !inconsistent_unit("column", j, col[j])
               && !inconsistent_unit("box", kB, box[kB])
               ) {
            j++;
            }
          } // if (i.. else
        } // if (initial[k][j]..
      else {
        j++;
        }
      this_time = clock()/CLOCKS_PER_SEC;
      if (this_time - start_time > BRUTE_MAX_TIME) {
        result = BRUTE_TIMEOUT;
        goto done;                                                        //==>
        }
      } while (j < 9);
    k++;
    j = 0;
    } while (k < 9);

done:
  return result;
  }

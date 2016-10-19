/* init.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "def.h"
#include "init.h"

void init() {

  // Initialize the sudoku arrays
  for (int k = 0; k < 9; k++) {
    for (int j = 0; j < 9; j++) {
      grid[k][j] = 0;
      row[k][j][0] = k;
      row[k][j][1] = j;
      col[j][k][0] = k;
      col[j][k][1] = j;
      box[k/3*3+j/3][k%3*3+j%3][0] = k;
      box[k/3*3+j/3][k%3*3+j%3][1] = j;
      }
    }
  }

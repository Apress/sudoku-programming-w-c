/* init.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "def.h"
#include "init.h"

void init(char *arg) {
#ifdef LOG_IN_OUT
  printf("--- init >>>\n");
#endif

  // Initialize the sudoku arrays
  for (int k = 0; k < 9; k++) {
    for (int j = 0; j < 9; j++) {
      grid[k][j][0] = 9;
      for (int i = 1; i <= 9; i++) {
        grid[k][j][i] = TRUE;
        }
      row[k][j][0] = k;
      row[k][j][1] = j;
      col[j][k][0] = k;
      col[j][k][1] = j;
      box[k/3*3+j/3][k%3*3+j%3][0] = k;
      box[k/3*3+j/3][k%3*3+j%3][1] = j;
      }
    }

  // Save the sudoku string into the array
  for (int k = 0; k < 81; k++) {
    int kR = k / 9;
    int kC = k - kR * 9;
    if (arg[k] != '0') {
      for (int i = 1; i <= 9; i++) {
        grid[kR][kC][i] = FALSE;
        }
      grid[kR][kC][arg[k] - '0'] = TRUE;
      grid[kR][kC][0] = 1;
      }
    }

/*
  // Display the allocated numbers
  for (int k = 0; k < 9; k++) {
    for (int j = 0; j < 9; j++) {
      if (grid[k][j][0] == 1) {
        int i = 0;
        do {
          i++;
          } while (grid[k][j][i] == 0);
        printf("%d", i);
        }
      else {
        printf(".");
        }
      }
    printf("\n");
    }
*/
#ifdef LOG_IN_OUT
  printf("<<< init ---\n");
#endif
  }

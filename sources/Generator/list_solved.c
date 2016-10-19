/* list_solved.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "def.h"
#include "list_solved.h"

void list_solved(FILE *fp) {
  if (fp == NULL) {
    fp = stdout;
    }
  char spacing = (fp == stdout) ? ' ' : '\t';
  int digits[10] = {0};
  for (int k = 0; k < 9; k++) {
    for (int j = 0; j < 9; j++) {
      if (grid[k][j] != 0) {
        digits[(int)grid[k][j]]++;
        }
      } // for (int j..
    } // for (int k..
  for (int i = 1; i <= 9; i++) {
    fprintf(fp, "%c%d", spacing, digits[i]);
    }
  }

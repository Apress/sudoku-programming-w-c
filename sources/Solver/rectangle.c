/* rectangle.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "def.h"
#include "rectangle.h"
#include "rectangle_cell.h"
#include "rectangle_pattern.h"

int rectangle() {
#ifdef LOG_IN_OUT
  printf("--- rectangle >>>\n");
#endif
  int result = FALSE;
  int pattern[9][4] = {
      {0,1,4,3}, {0,2,5,3}, {0,1,7,6},
      {0,2,8,6}, {1,2,5,4}, {1,2,8,7},
      {3,4,7,6}, {3,5,8,6}, {4,5,8,7}
      };
  for (int k = 0; k < 9  && !result; k++) {
    result = rectangle_pattern(pattern[k]);
    }
#ifdef LOG_IN_OUT
  printf("<<< rectangle ---\n");
#endif
  return result;
  }

/* box_line.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "box_line.h"
#include "box_line_unit.h"
#include "def.h"

int box_line() {
#ifdef LOG_IN_OUT
  printf("--- box_line >>>\n");
#endif
  int result = FALSE;
  for (int k = 0; k < 9  &&  !result; k++) {
    if (box_line_unit(ROW, row[k])  ||  box_line_unit(COL, col[k])) {
      result = TRUE;
      }
    }
#ifdef LOG_IN_OUT
  printf("<<< box_line ---\n");
#endif
  return result;
  }

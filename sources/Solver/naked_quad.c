/* naked_quad.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "def.h"
#include "naked_quad.h"
#include "naked_quad_unit.h"

int naked_quad() {
#ifdef LOG_IN_OUT
  printf("--- naked_quad >>>\n");
#endif
  int result = FALSE;
  for (int k = 0; k < 9  &&  !result; k++) {
    if (   naked_quad_unit("row", row[k])
        || naked_quad_unit("column", col[k])
        || naked_quad_unit("box", box[k])
        ) {
      result = TRUE;
      }
    }
#ifdef LOG_IN_OUT
  printf("<<< naked_quad ---\n");
#endif
  return result;
  }

/* naked_triple.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "def.h"
#include "naked_triple.h"
#include "naked_triple_unit.h"

int naked_triple() {
#ifdef LOG_IN_OUT
  printf("--- naked_triple >>>\n");
#endif
  int result = FALSE;
  for (int k = 0; k < 9  &&  !result; k++) {
    if (   naked_triple_unit("row", row[k])
        || naked_triple_unit("column", col[k])
        || naked_triple_unit("box", box[k])
        ) {
      result = TRUE;
      }
    }
#ifdef LOG_IN_OUT
  printf("<<< naked_triple ---\n");
#endif
  return result;
  }

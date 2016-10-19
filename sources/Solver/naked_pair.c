/* naked_pair.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "def.h"
#include "naked_pair.h"
#include "naked_pair_unit.h"

int naked_pair() {
#ifdef LOG_IN_OUT
  printf("--- naked_pair >>>\n");
#endif
  int result = FALSE;
  for (int k = 0; k < 9  &&  !result; k++) {
    if (   naked_pair_unit("row", row[k])
        || naked_pair_unit("column", col[k])
        || naked_pair_unit("box", box[k])
        ) {
      result = TRUE;
      }
    }
#ifdef LOG_IN_OUT
  printf("<<< naked_pair ---\n");
#endif
  return result;
  }

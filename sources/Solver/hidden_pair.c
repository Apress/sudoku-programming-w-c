/* hidden_pair.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "def.h"
#include "hidden_pair.h"
#include "hidden_pair_unit.h"

int hidden_pair() {
#ifdef LOG_IN_OUT
  printf("--- hidden_pair >>>\n");
#endif
  int result = FALSE;
  for (int k = 0; k < 9  &&  !result; k++) {
    if (   hidden_pair_unit("row", row[k])
        || hidden_pair_unit("column", col[k])
        || hidden_pair_unit("box", box[k])
        ) {
      result = TRUE;
      }
    }
#ifdef LOG_IN_OUT
  printf("<<< hidden_pair ---\n");
#endif
  return result;
  }

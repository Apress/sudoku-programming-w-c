/* hidden_triple.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "def.h"
#include "hidden_triple.h"
#include "hidden_triple_unit.h"

int hidden_triple() {
#ifdef LOG_IN_OUT
  printf("--- hidden_triple >>>\n");
#endif
  int result = FALSE;
  for (int k = 0; k < 9  &&  !result; k++) {
    if (   hidden_triple_unit("row", row[k])
        || hidden_triple_unit("column", col[k])
        || hidden_triple_unit("box", box[k])
        ) {
      result = TRUE;
      }
    }
#ifdef LOG_IN_OUT
  printf("<<< hidden_triple ---\n");
#endif
  return result;
  }

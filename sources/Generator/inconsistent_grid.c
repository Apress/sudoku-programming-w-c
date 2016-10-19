/* inconsistent_grid.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "def.h"
#include "inconsistent_grid.h"
#include "inconsistent_unit.h"

int inconsistent_grid() {
  int result = FALSE;
  for (int k = 0; k < 9 && !result; k++) {
    result |= inconsistent_unit("row", k, row[k]);
    if (!result) {
      result |= inconsistent_unit("column", k, col[k]);
      if (!result) {
        result |= inconsistent_unit("box", k, box[k]);
        }
      }
    } // for (int k..
  return result;
  }

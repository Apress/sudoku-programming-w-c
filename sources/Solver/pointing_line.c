/* pointing_line.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "def.h"
#include "pointing_line.h"
#include "pointing_line_box.h"

int pointing_line() {
#ifdef LOG_IN_OUT
  printf("--- pointing_line >>>\n");
#endif
  int result = FALSE;
  for (int k = 0; k < 9  &&  !result; k++) {
    result = pointing_line_box(k, box[k]);
    }
#ifdef LOG_IN_OUT
  printf("<<< pointing_line ---\n");
#endif
  return result;
  }

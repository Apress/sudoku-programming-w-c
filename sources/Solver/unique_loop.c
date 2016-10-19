/* unique_loop.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "def.h"
#include "unique.h"
#include "unique_loop.h"

int unique_loop() {
#ifdef LOG_IN_OUT
  printf("--- unique_loop >>>\n");
#endif
  int found;
  int something = FALSE;
  do {
    found = unique();
    something |= found;
    } while (found && !problem_found);
#ifdef LOG_IN_OUT
  printf("<<< unique_loop ---\n");
#endif
  return something;
  }

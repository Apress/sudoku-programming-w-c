/* solve.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "count_candidates.h"
#include "def.h"
#include "display.h"
#include "display_string.h"
#include "execute_strategies.h"
#include "keep_going.h"
#include "solve.h"

void solve() {
#ifdef LOG_IN_OUT
  printf("--- solve >>>\n");
#endif
  if (!backtracking) n_strats_used = 0;
  int n_candidates = count_candidates();
  int n_candidates_old = n_candidates + 1;

  while (keep_going()  &&  n_candidates < n_candidates_old) {
    n_candidates_old = n_candidates;
    if (keep_going()  &&  !execute_strategies(0)) {
      if (keep_going()  &&  !execute_strategies(1)) {
        if (keep_going()  &&  !execute_strategies(2)) {
          execute_strategies(3);
          }
        }
      }
    n_candidates = count_candidates();
    }
#ifdef LOG_IN_OUT
  printf("<<< solve ---\n");
#endif
  }

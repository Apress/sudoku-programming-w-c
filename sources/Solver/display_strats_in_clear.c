/* display_strats_in_clear.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "def.h"
#include "display_strats_in_clear.h"

void display_strats_in_clear() {
  for (int k = 0; k < n_strats_used; k++) {
    int level = strats_used[k] / 10;
    int k_strat = strats_used[k] - level * 10;
    printf(" '%s'", strat_all_names[level][k_strat]);
    }
  printf("\n");
  }

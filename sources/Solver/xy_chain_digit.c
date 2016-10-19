/* xy_chain_digit.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "def.h"
#include "pairs_data.h"
#include "xy_chain_digit.h"
#include "xy_chain_step.h"

int xy_chain_digit(int i0) {
#ifdef LOG_IN_OUT
  printf("--- xy_chain_digit (%d) >>>\n", i0);
#endif

  int n_found = 0;
  for (int i1 = 1; i1 <= 9 && n_found == 0; i1++) {
    for (int i01 = 0; i01 < n_x_pairs[i0][i1] && n_found == 0; i01++) {

      // Flag x_pairs[i0][i1][ROW][i01] and x_pairs[i0][i1][COL][i01]
      // to avoid using the same cell more than once within the chain
      int kR01 = x_pairs[i0][i1][ROW][i01];
      int kC01 = x_pairs[i0][i1][COL][i01];
      x_pairs[i0][i1][ROW][i01] += 10;
      x_pairs[i1][i0][ROW][i01] += 10;

      // Start the chain.
      {
        int kB01 = x_pairs[i0][i1][BOX][i01];
        chain_info_struct_t i0_info;
        chain_info_struct_t i1_info;
        i0_info.digit = i0;
        i1_info.digit = i1;
        i1_info.coords[ROW] = i0_info.coords[ROW] = kR01;
        i1_info.coords[COL] = i0_info.coords[COL] = kC01;
        i1_info.coords[BOX] = i0_info.coords[BOX] = kB01;
        i0_info.next = &i1_info;
        i1_info.next = NULL;
        n_found += xy_chain_step(&i0_info, 1);
        }

      // Restore the grid.
      x_pairs[i0][i1][ROW][i01] -= 10;
      x_pairs[i1][i0][ROW][i01] -= 10;
      } // for (int i01..
    } // for (int i1 = 1..

#ifdef LOG_IN_OUT
  printf("<<< xy_chain_digit (%d) ---\n", i0);
#endif
  return n_found > 0;
  }

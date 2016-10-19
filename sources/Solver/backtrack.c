/* backtrack.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "backtrack.h"
#include "cleanup_around.h"
#include "count_solved.h"
#include "def.h"
#include "display_strats_in_clear.h"
#include "solve.h"

#define MAX_DEPTH 10

int backtrack(int depth) {
#ifdef LOG_IN_OUT
  printf("--- backtrack (%d) >>>\n", depth);
#endif

  int result = FALSE;
  char grid_backup[9][9][10];

  // Select the cell
  int k;
  int j;
  {
    int max_i = -1;
    int row_max_i;
    int col_max_i;
    for (k = 0; k < 9 && max_i < 9; k++) {
      for (j = 0; j < 9 && max_i < 9; j++) {
        if (grid[k][j][0] > max_i) {
          max_i = grid[k][j][0];
          row_max_i = k;
          col_max_i = j;
          }
        }
      }
    k = row_max_i;
    j = col_max_i;
    }

  // Process the cell
  char *elem = grid[k][j];
  if (!silent) {
    for (int kd = 0; kd < depth; kd++) printf("  ");
    printf("backtrack (%d): (%d,%d) has candidates", depth, k, j);
    for (int i = 1; i <= 9; i++) {
      if (elem[i]) printf(" %d", i);
      }
    printf("\n");
    } // if (!silent..
  for (int i = 1; i <= 9 && !result; i++) {
    if (elem[i]) {

      // Save the current state of the grid
      for (int k1 = 0; k1 < 9; k1++) {
        for (int j1 = 0; j1 < 9; j1++) {
          for (int i1 = 0; i1 <= 9; i1++) {
            grid_backup[k1][j1][i1] = grid[k1][j1][i1];
            }
          } // for (int j1..
        } // for (int k1..

      // Force a solution
      for (int i1 = 1; i1 <= 9; i1++) {
        elem[i1] = FALSE;
        }
      elem[i] = TRUE;
      elem[0] = 1;
      int orig_silent = silent;
      silent = TRUE;
      cleanup_around(k, j);

      // Attempt to solve the puzzle
      solve();
      silent = orig_silent;

      // Check the result
      if (problem_found) {
        problem_found = FALSE;
        if (!silent) {
          for (int kd = 0; kd < depth; kd++) printf("  ");
          printf("backtrack (%d): %d unsuccessful\n", depth, i);
          }
        } // if (problem_found..
      else {
        if (!silent) {
          for (int kd = 0; kd < depth; kd++) printf("  ");
          printf("backtrack (%d): %d successful (%d solved)\n",
              depth, i, count_solved()
              );
          for (int kd = 0; kd < depth; kd++) printf("  ");
          printf("backtrack (%d) strategies:", depth);
          if (n_strats_used > 0) display_strats_in_clear();
          else printf("none");
          printf("\n");
          }
        if (count_solved() == 81) {
          strats_used[n_strats_used] = 40 + depth;
          n_strats_used++;
          result = TRUE;
          }
        else if (depth < MAX_DEPTH) {
          result = backtrack(depth + 1);
          }
        } // if (problem_found.. else..

      // If unsuccessful, restore the grid to its original content
      if (!result) {
        for (int k1 = 0; k1 < 9; k1++) {
          for (int j1 = 0; j1 < 9; j1++) {
            for (int i1 = 0; i1 <= 9; i1++) {
              grid[k1][j1][i1] = grid_backup[k1][j1][i1];
              }
            } // for (int j1..
          } // for (int k1..
        } // if (!result
      } // if (elem[i]..
    } // for (int i..

#ifdef LOG_IN_OUT
  printf("<<< backtrack (%d) ---\n", depth);
#endif
  return result;
  }

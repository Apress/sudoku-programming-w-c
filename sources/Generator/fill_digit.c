/* fill_digit.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "def.h"
#include "fill_digit.h"

int fill_digit(char i) {
  const int other_box[9][2][2] = {  // [this box][row/column][..]
              {/* 0 */ {-1    }, {-1    }},
              {/* 1 */ { 0, -1}, {-1    }},
              {/* 2 */ { 0,  1}, {-1    }},
              {/* 3 */ {-1    }, { 0, -1}},
              {/* 4 */ { 3, -1}, { 1, -1}},
              {/* 5 */ { 3,  4}, { 2, -1}},
              {/* 6 */ {-1    }, { 0,  3}},
              {/* 7 */ { 6, -1}, { 1,  4}},
              {/* 8 */ { 6,  7}, { 2,  5}},
            };
  int solved_cells[2][9] = {{-1, -1, -1, -1, -1, -1, -1, -1, -1}};

  int problem_found = FALSE;
  int n_cells;
  int cell[9][2];
  for (int kB = 0; kB < 9 && !problem_found; kB++) {
    problem_found = TRUE;
    n_cells = 0;
    for (int k = 0; k < 9; k++) {
      int kR = box[kB][k][ROW];
      int kC = box[kB][k][COL];
      if (grid[kR][kC] == 0) {
        int rc[2];
        rc[ROW] = kR;
        rc[COL] = kC;
        int conflict = FALSE;
        for (int kRC = 0; kRC < 2 && !conflict; kRC++) {
          int kkS = other_box[kB][kRC][0];
          if (kkS >= 0) {
            if (rc[kRC] == solved_cells[kRC][kkS]) {
              conflict = TRUE;
              }
            else {
              kkS = other_box[kB][kRC][1];
              if (kkS >= 0 && rc[kRC] == solved_cells[kRC][kkS]) {
                conflict = TRUE;
                }
              }
            } // if (kkS..
          } // for (int kRC..

        if (!conflict) {
          cell[n_cells][ROW] = kR;
          cell[n_cells][COL] = kC;
          n_cells++;
          }
        } // if (grid[kR][kC]..
      } // for (int k..

    // Pick a cell of the box
    if (n_cells > 0) {
      problem_found = FALSE;
      int kE = rand() % n_cells;
      solved_cells[ROW][kB] = cell[kE][ROW];
      solved_cells[COL][kB] = cell[kE][COL];
      grid[solved_cells[ROW][kB]][solved_cells[COL][kB]] = i;
      }

    } // for (int kB..

  if (problem_found) {

    // Restore the grid to its initial status
    for (int m = 0; m < 9 && solved_cells[ROW][m] >= 0; m++) {
      grid[solved_cells[ROW][m]][solved_cells[COL][m]] = 0;
      }
    }
  return problem_found;
  }

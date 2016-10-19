/* sudoku_gen.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "brute_comp.h"
#include "count_solved.h"
#include "def.h"
#include "display.h"
#include "display_string.h"
#include "fill.h"
#include "inconsistent_grid.h"
#include "inconsistent_unit.h"
#include "init.h"
#include "in_box.h"
#include "list_solved.h"
#include "multi_html.h"
#include "save_html.h"

#define LOG_TO_FILE___NO
#define FILE_NAME "puzzles.txt"

#define SAVE_HTML_PUZZLE
#define SAVE_HTML_SOLUTION

#define DO_PATTERN___NO

// N_GRIDS is defined in multi_html.h.
// When N_GRIDS is between 2 and 5, it triggers the creation of multi-grid
// puzzles. With any other value, the Generator creates a classic Sudoku.
#define DO_MULTI_GRID (N_GRIDS >= 2  &&  N_GRIDS <= 5)

// Parameters
#define N_SET_QUADS 5
#define N_SET_PAIRS 10
#define N_SET_CELLS 0
#define ADDITIONAL_CELLS TRUE
#define FIRST_SEED 12345
#define N_SEEDS 1

// Global variables
char *unit_names[3] = {"row", "column", "box"};
char grid[9][9];
char row[9][9][2];
char col[9][9][2];
char box[9][9][2];
char solved[9][9];
int silent = TRUE;

// Variables and functions local to this module
char puzzle[9][9];
int r_1[81];
int c_1[81];
int k_cell;
int remove_quads(int k_puz);
int remove_pairs(int k_puz);
void make_clue_list(void);
int remove_clues(int k_puz);
void remove_more_clues(int k_puz);
int check_uniqueness(void);

// The following table identifies the box of grid 0 that overlaps with other
// grids when creating multi-grid Sudokus.
// The first box refers to puzzle0 and second one to the other puzzle:
//
// N_GRIDS  kPuz=1  kPuz=2  kPuz=3  kPuz=4
//     2    b0-b8
//     3    b0-b8   b8-b0
//     4    b0-b8   b8-b0   b2-b6
//     5    b0-b8   b8-b0   b2-b6   b6-b2
//
// Puzzle:     0   1   2   3   4
int box0[] = {-1,  0,  8,  2,  6};

#ifdef DO_PATTERN
const char KEEP0[82] =
    "..1.1.1.."
    ".1..1..1."
    "1..1.1..1"
    "..1...1.."
    "11..1..11"
    "..1...1.."
    "1..1.1..1"
    ".1..1..1."
    "..1.1.1.."
    ;
const char KEEP1[82] =
    "..11111.."
    ".1.....1."
    "1..111..1"
    "1.1...1.1"
    "1.1.1.1.1"
    "1.1...1.1"
    "1..111..1"
    ".1.....1."
    "..11111.."
    ;
const char KEEP2[82] =
    "..11111.."
    ".1.....1."
    "1..111..1"
    "1.1...1.1"
    "1.1.1.1.1"
    "1.1...1.1"
    "1..111..1"
    ".1.....1."
    "..11111.."
    ;
const char KEEP3[] =
    "..11111.."
    ".1.....1."
    "1..111..1"
    "1.1...1.1"
    "1.1.1.1.1"
    "1.1...1.1"
    "1..111..1"
    ".1.....1."
    "..11111.."
    ;
const char KEEP4[] =
    "..11111.."
    ".1.....1."
    "1..111..1"
    "1.1...1.1"
    "1.1.1.1.1"
    "1.1...1.1"
    "1..111..1"
    ".1.....1."
    "..11111.."
    ;
const char *KEEPS[5] = { KEEP0, KEEP1, KEEP2, KEEP3, KEEP4 };
#endif

//======================================================================== main
int main(int argc, char *argv[]) {
  printf("*** sudoku_gen ***\n");
  char mess[32];
  int n_seeds = N_SEEDS;
  int k_try = 0;

#if DO_MULTI_GRID
  // When creating multi-grid puzzles, set n_seed to the number of
  // puzzles that you need
  n_seeds = N_GRIDS;
#endif

  // Open a file to log the results
  FILE *fp = NULL;
#ifdef LOG_TO_FILE
  fp = fopen(FILE_NAME, "a");
  if (fp == NULL) {
    printf("Unable to open the file '%s' for reading\n", FILE_NAME);
    return EXIT_FAILURE;                                                  //==>
    }
#endif

  // Try all the seeds in the given range
  unsigned long start_time = clock();

  for (int k_seed = 0; k_seed < n_seeds; k_seed++) {
    int seed = FIRST_SEED + k_seed;
    srand(seed);
    int brute_result;
    int n;

    // Keep repeating the generation until you find a unique solution
    char puzzle_string[82];
    char solution_string[82];
    do {

      // Generate a solved Sudoku
      do { init(); } while (fill());

      // Save the solved Sudoku
      for (int k = 0; k < 9; k++) {
        for (int j = 0; j < 9; j++) {
          solved[k][j] = grid[k][j];
          puzzle[k][j] = grid[k][j];
          }
        }

#if DO_MULTI_GRID
      if (k_seed > 0) {
        // You arrive here if you are creating a multi-grid puzzle and
        // have already created the first one (puzzle 0).
        int k0 = box0[k_seed]/3*3;
        int j0 = box0[k_seed]%3*3;
        int kk = overlapping_box[k_seed]/3*3;
        int jj = overlapping_box[k_seed]%3*3;

        // Build the look-up list of numbers to match puzzle 0 when creating
        // subsequent grids.
        char map[10] = {0};
        for (int k = 0; k < 3; k++) {
          for (int j = 0; j < 3; j++) {
            map[(int)grid[(kk + k)][jj + j]] =
                multi_string[0][SOL][(k0 + k)*9 + j0 + j] - '0'
                ;
            }
          }

        // Convert the numbers in the grid and save the modified grid
        for (int k = 0; k < 9; k++) {
          for (int j = 0; j < 9; j++) {
            grid[k][j] = map[(int)grid[k][j]];
            solved[k][j] = grid[k][j];
            puzzle[k][j] = grid[k][j];
            }
          }
#ifndef DO_PATTERN
        // Make the box that overlaps puzzle 0 identical to the
        // corresponding one of puzzle 0
        for (int k = 0; k < 3; k++) {
          for (int j = 0; j < 3; j++) {
            grid[(kk + k)][jj + j] =
                multi_string[0][PUZ][(k0 + k)*9 + j0 + j] - '0'
                ;
            }
          }
#endif
        }
#endif

#ifdef DO_PATTERN
      for (int i = 0; i < 81; i++) {
        if (KEEPS[k_seed][i] == '.') {
          int k = i / 9;
          int j = i - k * 9;
          grid[k][j] = 0;
          puzzle[k][j] = 0;
          }
        }
#else
      //========= Remove N_SET_QUADS quadruples of clues
      if (N_SET_QUADS > 0) {
        int success = remove_quads(k_seed);
        if (!success) {
          brute_result = BRUTE_COMP_DIFFERENT;
          goto skip;                                                      //==>
          }
        }

      //========= Remove N_SET_PAIRS pairs of clues
      if (N_SET_PAIRS > 0) {
        int success = remove_pairs(k_seed);
        if (!success) {
          brute_result = BRUTE_COMP_DIFFERENT;
          goto skip;                                                      //==>
          }
        }

      //========= Remove N_SET_CELLS individual clues and then some more
      make_clue_list();
      k_cell = 0;
      if (N_SET_CELLS > 0) {
        int success = remove_clues(k_seed);
        if (!success) {
          brute_result = BRUTE_COMP_DIFFERENT;
          goto skip;                                                      //==>
          }
        }
      if (ADDITIONAL_CELLS && k_cell < 81) remove_more_clues(k_seed);
#endif

      //========= Check whether the solution is really unique
      brute_result = check_uniqueness();

      //========= Done
      for (int k = 0; k < 9; k++) {
        for (int j = 0; j < 9; j++) {
          grid[k][j] = puzzle[k][j];
          }
        }
      n = count_solved();
      if (!silent && fp == NULL) {
        display();
        sprintf(mess, "seed %d %d", seed, n);
        display_string(mess);
        printf("The puzzle contains %d clues:", n);
        list_solved(stdout);
        }

skip:                                                                    // <==
      k_try++;
      printf("%d: %s\n",
          k_try,
          (brute_result == BRUTE_COMP_DIFFERENT) ? "No" : "Yes"
          );
      } while (brute_result == BRUTE_COMP_DIFFERENT);

    // Save puzzle and solution into strings
    int kar = 0;
    for (int k = 0; k < 9; k++) {
      for (int j = 0; j < 9; j++) {
        puzzle_string[kar] = puzzle[k][j] + '0';
        solution_string[kar] = solved[k][j] + '0';
        kar++;
        }
      }
    puzzle_string[kar] = '\0';
    solution_string[kar] = '\0';

#if DO_MULTI_GRID
    // Save the puzzle and solution strings to be combined later into
    // a multi-grid Sudoku
    for (int i = 0; i < 82; i++) { // copy also the '\0' at the end
      multi_string[k_seed][PUZ][i] = puzzle_string[i];
      multi_string[k_seed][SOL][i] = solution_string[i];
      }
#endif

#ifdef SAVE_HTML_PUZZLE
    save_html(puzzle_string, seed, "p");
#endif

#ifdef SAVE_HTML_SOLUTION
    save_html(solution_string, seed, "s");
#endif
    if (fp != NULL) {
      printf("#%d\n", k_seed);
      fprintf(fp, "%s\t%d", puzzle_string, seed);
      if (brute_result != BRUTE_COMP_DIFFERENT) {
        fprintf(fp, "\t%d", n);
        list_solved(fp);
        }
      fprintf(fp, "\n");
      }
    } // for (k_seed..

#if DO_MULTI_GRID
  multi_html(FIRST_SEED, PUZ);
  multi_html(FIRST_SEED, SOL);
#endif

  unsigned long end_time = clock();
  printf("********* done in %ld microseconds\n", end_time - start_time);
  if (fp != NULL) fclose(fp);
  return EXIT_SUCCESS;
  }

//================================================================ remove_quads
#define N_QUADS 20
int remove_quads(int kPuz) {

  // Build a random list of cells to be quadrupled
  int r_4[N_QUADS];
  int c_4[N_QUADS];
  {
    char quads[9][9] = {{0}};
    for (int k = 0; k < N_QUADS; k++) {
      int kR;
      int kC;
      do {
        int kk = rand() % N_QUADS;
        kR = kk >> 2;
        kC = kk - (kR << 2);
        } while (quads[kR][kC] > 0);
      r_4[k] = kR;
      c_4[k] = kC;
      quads[kR][kC] = 1;
      }
    }

  // Change quadruples until you get a matching solution
  int k_quad = -1;
  int n_quads = 0;
  while (n_quads < N_SET_QUADS && k_quad < N_QUADS-1) {
    k_quad++;
    n_quads++;
    int quad[4][2] = {{0}}; // [index][row/col]
    int kR = r_4[k_quad];
    int kC = c_4[k_quad];
    quad[0][ROW] = kR;
    quad[0][COL] = kC;
    quad[1][ROW] = kR;
    quad[1][COL] = 8 - kC;
    if (kR == 4) {
      quad[2][ROW] = kC;
      quad[2][COL] = kR;
      quad[3][ROW] = 8 - kC;
      quad[3][COL] = kR;
      }
    else {
      quad[2][ROW] = 8 - kR;
      quad[2][COL] = kC;
      quad[3][ROW] = 8 - kR;
      quad[3][COL] = 8 - kC;
      }
    if (!silent) printf("Removed quad %d:", k_quad);
    for (int k = 0; k < 4; k++) {
      int kR = quad[k][ROW];
      int kC = quad[k][COL];

      // The following 'if' is only needed when creating multi-grid puzzles
      if (kPuz == 0  ||  !in_box(kR, kC, overlapping_box[kPuz])) {
        grid[kR][kC] = 0;
        }
      if (!silent) printf("(%d,%d)", kR, kC);
      }
    if (!silent) printf("\n");

    // Save the Sudoku puzzle after the removal
    for (int k = 0; k < 9; k++) {
      for (int j = 0; j < 9; j++) {
        puzzle[k][j] = grid[k][j];
        }
      }

    // Solve with brute() and see whether the solution matches
    // the reference
    int brute_result = brute_comp();
    if (!silent) printf("Brute after removing quad %d: %s\n",
        k_quad, brute_comp_err[brute_result]
        );

    // If not, backtrack
    if (brute_result != BRUTE_COMP_OK) {
      if (!silent) printf("Backtracking the last quadruple\n");
      puzzle[kR][kC] = solved[kR][kC];
      puzzle[kR][8-kC] = solved[kR][8-kC];
      puzzle[8-kR][kC] = solved[8-kR][kC];
      puzzle[8-kR][8-kC] = solved[8-kR][8-kC];
      n_quads--;
      }

    // Restore the puzzle to how it was before solving it
    for (int k = 0; k < 9; k++) {
      for (int j = 0; j < 9; j++) {
        grid[k][j] = puzzle[k][j];
        }
      }
    } // while (n_quads..
  int success = n_quads == N_SET_QUADS;
  if (!silent) {
    if (success) {
      printf("%d clues left after removing the quadruples\n", count_solved());
      display();

      // Save the Sudoku puzzle after removing the quadruples
      for (int k = 0; k < 9; k++) {
        for (int j = 0; j < 9; j++) {
          grid[k][j] = puzzle[k][j];
          }
        }
      }
    else {
      printf("No unique solution when removing quadruples. Run aborted.\n");
      }
    }
  return success;
  } // remove_quads

//================================================================ remove_pairs
#define N_PAIRS 40
int remove_pairs(int kPuz) {

  // Build a random list of cells to be paired
  int r_2[N_PAIRS];
  int c_2[N_PAIRS];
  {
    char pairs[9][9] = {{0}};
    for (int k = 0; k < N_PAIRS; k++) {
      int kR;
      int kC;
      do {
        int kk = rand() % N_PAIRS;
        kR = kk / 9;
        kC = kk - kR * 9;
        } while (pairs[kR][kC] > 0);
      r_2[k] = kR;
      c_2[k] = kC;
      pairs[kR][kC] = 1;
      }
    }

  // Change pairs until you get a matching solution
  int k_pair = -1;
  int n_pairs = 0;
  while (n_pairs < N_SET_PAIRS && k_pair < N_PAIRS-1) {
    int kR;
    int kC;
    do {
      k_pair++;
      if (k_pair < N_PAIRS) {
        kR = r_2[k_pair];
        kC = c_2[k_pair];
        if (grid[kR][kC] == 0) {
          if (!silent) printf("Pair %d: (%d,%d) (%d,%d) overlaps"
              " with quadruple\n", k_pair, kR, kC, 8-kR, 8-kC
              );
          }
        }
      } while (grid[kR][kC] == 0 && k_pair < N_PAIRS);
    if (k_pair < N_PAIRS) {

      // The following two 'if' are only needed when creating multi-grid puzzles
      if (kPuz == 0  ||  !in_box(kR, kC, overlapping_box[kPuz])) {
        grid[kR][kC] = 0;
        }
      if (kPuz == 0  ||  !in_box(8 - kR, 8 - kC, overlapping_box[kPuz])) {
        grid[8-kR][8-kC] = 0;
        }
      n_pairs++;
      if (!silent) printf("Removed pair %d: (%d,%d) (%d,%d)\n",
          k_pair, kR, kC, 8-kR, 8-kC
          );

      // Save the Sudoku puzzle after the removal
      for (int k = 0; k < 9; k++) {
        for (int j = 0; j < 9; j++) {
          puzzle[k][j] = grid[k][j];
          }
        }

      // Solve with brute() and see whether the solution matches
      // the reference
      int brute_result = brute_comp();
      if (!silent) printf("Brute after removing pair %d: %s\n",
          k_pair, brute_comp_err[brute_result]
          );

      // If not, backtrack
      if (brute_result != BRUTE_COMP_OK) {
        if (!silent) printf("Backtracking the last pair\n");
        puzzle[kR][kC] = solved[kR][kC];
        puzzle[8-kR][8-kC] = solved[8-kR][8-kC];
        n_pairs--;
        }

      // Restore the puzzle to how it was before solving it
      for (int k = 0; k < 9; k++) {
        for (int j = 0; j < 9; j++) {
          grid[k][j] = puzzle[k][j];
          }
        }
      } // if (k_pair..
    } // while (n_pairs..

  int success = n_pairs == N_SET_PAIRS;
  if (!silent) {
    if (success) {
      printf("%d clues left after removing the pairs\n", count_solved());
      display();

      // Save the Sudoku puzzle after removing the pairs
      for (int k = 0; k < 9; k++) {
        for (int j = 0; j < 9; j++) {
          grid[k][j] = puzzle[k][j];
          }
        }
      }
    else {
      printf("No unique solution when removing pairs. Run aborted.\n");
      }
    }
  return success;
  } // remove_pairs

//============================================================== make_clue_list
void make_clue_list() {
  char singles[9][9] = {{0}};
  for (int k = 0; k < 81; k++) {
    int kR;
    int kC;
    do {
      int kk = rand() % 81;
      kR = kk / 9;
      kC = kk - kR * 9;
      } while (singles[kR][kC] > 0);
    r_1[k] = kR;
    c_1[k] = kC;
    singles[kR][kC] = 1;
    }
  } // make_clue_list

//================================================================ remove_clues
int remove_clues(int kPuz) {
  int success = TRUE;
  int n_cells = 0;
  while (n_cells < N_SET_CELLS && success) {
    int kR;
    int kC;
    do {
      kR = r_1[k_cell];
      kC = c_1[k_cell];
      if (grid[kR][kC] == 0) {
        if (!silent) printf("1 Cell %d: (%d,%d) overlaps with quadruple"
            " or pair\n", k_cell, kR, kC
            );
        }
      k_cell++;
      } while (grid[kR][kC] == 0 && k_cell < 81);
    if (k_cell > 81) {
      if (!silent) printf("1 No more cells available after removing"
          " %d clues. Run aborted.\n", n_cells
          );
      success = FALSE;
      }
    // The following 'if' is only needed when creating multi-grid puzzles
    else if (kPuz == 0  ||  !in_box(kR, kC, overlapping_box[kPuz])) {
      grid[kR][kC] = 0;
      n_cells++;
      if (!silent) printf("1 Clue removal %d, removed"
          " cell %d: (%d,%d)\n", n_cells, k_cell-1, kR, kC
          );

      // Save the Sudoku puzzle after the removal
      for (int k = 0; k < 9; k++) {
        for (int j = 0; j < 9; j++) {
          puzzle[k][j] = grid[k][j];
          }
        }

      // Solve with brute() and see whether the solution matches
      // the reference
      int brute_result = brute_comp();
      if (!silent) printf("1 Brute after removing cell %d: %s\n",
          k_cell-1, brute_comp_err[brute_result]
          );

      // If not, backtrack
      if (brute_result != BRUTE_COMP_OK) {
        if (!silent) printf("1 Backtracking the last cell\n");
        puzzle[kR][kC] = solved[kR][kC];
        n_cells--;
        }

      // Restore the puzzle to how it was before solving it
      for (int k = 0; k < 9; k++) {
        for (int j = 0; j < 9; j++) {
          grid[k][j] = puzzle[k][j];
          }
        }
      } // if (k_cell.. else ..
    } // while (n_cells..

  if (success) {

    // Save the Sudoku puzzle after removing the individual clues
    for (int k = 0; k < 9; k++) {
      for (int j = 0; j < 9; j++) {
        grid[k][j] = puzzle[k][j];
        }
      }
    if (!silent) {
      printf("%d clues left after removing %d individual clues\n",
        count_solved(), n_cells
        );
      display();
      }
    }
  return success;
  } // remove_clues

//=========================================================== remove_more_clues
void remove_more_clues(int kPuz) {
  int brute_result;
  do {
    int kR;
    int kC;
    do {
      kR = r_1[k_cell];
      kC = c_1[k_cell];
      if (grid[kR][kC] == 0) {
        if (!silent) printf("2 Cell %d: (%d,%d) overlaps with quadruple"
            " or pair\n", k_cell, kR, kC
            );
        }
      k_cell++;
      } while (grid[kR][kC] == 0 && k_cell < 81);

    // The second part of the following 'if' is only needed when creating
    // multi-grid puzzles
    if (k_cell <= 81  &&
        (kPuz == 0  ||  !in_box(kR, kC, overlapping_box[kPuz]))
        ) {
      grid[kR][kC] = 0;
      if (!silent) printf("2 Clue removal %d, removed"
          " cell %d: (%d,%d)\n", 81-count_solved(), k_cell-1, kR, kC
          );

      // Save the Sudoku puzzle after the removal
      for (int k = 0; k < 9; k++) {
        for (int j = 0; j < 9; j++) {
          puzzle[k][j] = grid[k][j];
          }
        }

      // Solve with brute() and see whether the solution matches the reference
      brute_result = brute_comp();
      if (!silent) printf("2 Brute after removing cell %d: %s\n",
          k_cell-1, brute_comp_err[brute_result]
          );

      // Restore the puzzle to how it was before solving it
      for (int k = 0; k < 9; k++) {
        for (int j = 0; j < 9; j++) {
          grid[k][j] = puzzle[k][j];
          }
        }
      } // if (k_cell..
    } while (brute_result == BRUTE_COMP_OK && k_cell < 81);

  // Restore the last clue removed
  if (brute_result != BRUTE_COMP_OK) {
    int kR = r_1[k_cell-1];
    int kC = c_1[k_cell-1];
    puzzle[kR][kC] = solved[kR][kC];
    }
  } // remove_more_clues

//============================================================ check_uniqueness
int check_uniqueness() {
  int brute_result = BRUTE_COMP_OK;
  int incr = -8;
  while (incr < 9 && brute_result != BRUTE_COMP_DIFFERENT) {
    for (int k = 0; k < 9 && brute_result != BRUTE_COMP_DIFFERENT; k++) {
      for (int j = 0; j < 9 && brute_result != BRUTE_COMP_DIFFERENT; j++) {
        if (puzzle[k][j] == 0) {
          for (int kk = 0; kk < 9; kk++) {
            for (int jj = 0; jj < 9; jj++) {
              grid[kk][jj] = puzzle[kk][jj];
              } // for (int jj..
            } // for (int kk..
          grid[k][j] = solved[k][j] + incr;
          int kB = k/3*3+j/3;
          if (    grid[k][j] < 1
               || grid[k][j] > 9
               || inconsistent_unit("row", k, row[k])
               || inconsistent_unit("column", j, col[j])
               || inconsistent_unit("box", kB, box[kB])
               ) {
            grid[k][j] = 0;
            }
          else {
            brute_result = brute_comp();
            } // if (grid[k][j]..
          } // if (puzzle[k]j]..
        } // for (int j..
      } // for (int k..
    incr++;
    if (incr == 0) incr++;
    } // while (incr..
  return brute_result;
  } // check_uniqueness

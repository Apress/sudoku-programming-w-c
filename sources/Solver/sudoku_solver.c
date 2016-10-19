/* sudoku_solver.c
 *
 * Main program.
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "backtrack.h"
#include "box_line.h"
#include "cleanup.h"
#include "count_candidates.h"
#include "count_solved.h"
#include "def.h"
#include "display.h"
#include "display_strats_in_clear.h"
#include "display_string.h"
#include "hidden_pair.h"
#include "hidden_triple.h"
#include "inconsistent_grid.h"
#include "init.h"
#include "lines_2.h"
#include "lines_3.h"
#include "lines_4.h"
#include "naked_pair.h"
#include "naked_quad.h"
#include "naked_triple.h"
#include "pointing_line.h"
#include "rectangle.h"
#include "solve.h"
#include "unique_loop.h"
#include "xy_chain.h"
#include "y_wing.h"

#define USE_FILES___NO
#define N_LEVELS 4  // levels of strategies

// Sudoku grid and Sudoku indexing arrays
char grid[9][9][10];
char row[9][9][2];
char col[9][9][2];
char box[9][9][2];

// unit names used for display in clear
char *unit_names[3] = {"row", "column", "box"};

// Arrays of strategies
//
// Trivial strategies (level 0)
f_ptr_t strat0[] = {unique_loop};
char *strat0_names[] = {
    "unique-loop"
    };
//
// Easy strategies (level 1)
f_ptr_t strat1[] = {naked_pair, hidden_pair, box_line, pointing_line};
char *strat1_names[] = {
    "naked-pair", "hidden-pair", "box-line", "pointing-line"
    };
//
// Intermediate strategies (level 2)
f_ptr_t strat2[] = {naked_triple, hidden_triple, lines_2,
    naked_quad, y_wing
    };
char *strat2_names[] = {
    "naked-triple", "hidden-triple", "lines-2", "naked-quad", "Y-wing"
    };
//
// Complex strategies (level 3)
f_ptr_t strat3[] = {rectangle, xy_chain, lines_3, lines_4};
char *strat3_names[] = {
    "rectangle", "XY-chain", "lines-3", "lines-4"
    };
//
// All strategies
f_ptr_t *strat_all[] = {
    &strat0[0], &strat1[0], &strat2[0], &strat3[0]
    };
char **strat_all_names[] = {
    &strat0_names[0], &strat1_names[0], &strat2_names[0], &strat3_names[0]
    };
int n_strat_all[] = {
    sizeof(strat0)/sizeof(f_ptr_t),
    sizeof(strat1)/sizeof(f_ptr_t),
    sizeof(strat2)/sizeof(f_ptr_t),
    sizeof(strat3)/sizeof(f_ptr_t)
    };
int n_levels = N_LEVELS;

// List of used strategies (never seen more than 27)
int strats_used[50];
int n_strats_used;

// Global flags, to 'pop out' from nested loops and calls
int problem_found = FALSE;
int silent = FALSE;
int backtracking = FALSE;

//==================================================================== main
int main(int argc, char *argv[]) {
  printf("*** sudoku_solver ***\n");

#ifdef USE_FILES

  char *infile = "puzzles.txt";
  char *outfile = "solutions.txt";
  FILE *fpr = fopen(infile, "r");
  FILE *fpw = fopen(outfile, "a");
  if (fpr == NULL) {
    printf("File \"%s\" failed to open\n", infile);
    }
  else if (fpw == NULL) {
    printf("File \"%s\" failed to open\n", outfile);
    }
  else {
    silent = TRUE;

    // Keep reading from file until you reach the EOF
    int n_lines = 0;
    int n_hints = 0;
    while (!feof(fpr) && n_hints >= 0) {
      char line[100];  // 90 would be enough, but...
      line[0] = '\0';
      (void)fgets(line, 99, fpr);
      if (line != NULL && strlen(line) > 80) {
        char sudoku_s[82];
        int seed;
        n_hints = -1;
        sscanf(line, "%s\t%d\t%d", sudoku_s, &seed, &n_hints);
        if (n_hints > 0) {
          fprintf(fpw, "%s\t%d\t%d", sudoku_s, seed, n_hints);
          init(sudoku_s);
          cleanup();
          solve();
          if (count_solved() < 81) {
            backtracking = TRUE;
            backtrack(0);
            backtracking = FALSE;
            }
          printf("%d\n", n_lines);
          fprintf(fpw, "\t%s\t%d\t%d",
             inconsistent_grid() ? "inconsistent" : "consistent",
             count_solved(),
             n_strats_used
             );
          for (int k = 0; k < n_strats_used; k++) {
            fprintf(fpw, "\t%d", strats_used[k]);
            }
          fprintf(fpw, "\n");
          n_lines++;
          } // if (n_hints..
        } // if (line..
      } // while (TRUE..
    } // if (fpr .. else ..
  if (fpr != NULL) fclose(fpr);
  if (fpw != NULL) fclose(fpw);

#else

  // Check for the presence of an input Sudoku string
  if (argc < 2) {
    puts("*** You need to provide a sudoku string");
    return EXIT_FAILURE;
    }

  // Check that the Sudoku string is 81-characters long
  if (strlen(argv[1]) != 81) {
    puts("*** The sudoku string must be 81 characters long");
    return EXIT_FAILURE;
    }

  // Check that the Sudoku string consists of digits between 0 and 9
  for (int k = 0; k < 81; k++) {
    if (argv[1][k] < '0' || argv[1][k] > '9') {
      puts("*** The sudoku string must only contain 0 to 9 digits");
      return EXIT_FAILURE;
      }
    }

  // Print the Sudoku string
  if (argc > 2) {
    printf("--- \"%s\"\n", argv[2]);
    }
  printf("--- \"%s\"\n", argv[1]);

  // Initialize the Sudoku arrays
  init(argv[1]);
  display();

  // Remove the impossible numbers with an initial cleanup without
  // displaying any logging messages
  printf("sudoku: the initial grid contains %d solved cells\n",
      count_solved()
      );
  silent = TRUE;
  cleanup();
  silent = FALSE;
  printf("sudoku: after the initial cleanup, the grid"
      " contains %d solved cells\n", count_solved()
      );
  display();

  // Execute the strategies
  solve();

  // Backtrack if necessary
  if (count_solved() < 81) {
    backtracking = TRUE;
    backtrack(0);
    backtracking = FALSE;
    }


  // Check that everything is OK
  if (inconsistent_grid()) {
    printf("*** The grid is inconsistent\n");
    }

  printf("sudoku: the final grid contains %d solved cells\n",
      count_solved()
      );
  display();
  display_string();
  printf("Strategies used %d:", n_strats_used);
/*
  for (int k = 0; k < n_strats_used; k++) {
    printf(" %d", strats_used[k]);
    }
  printf("\n");
*/
  display_strats_in_clear();

#endif

  return EXIT_SUCCESS;
  }

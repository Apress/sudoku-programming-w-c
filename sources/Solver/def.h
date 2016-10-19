/* def.h
 *
 * Definitions and declarations
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#ifndef DEF
#define DEF

// General definitions
#define FALSE 0
#define TRUE  1

// Definitions for logging
#define LOG_FOOTPRINT
#define LOG_HIDDEN_PAIR
#define LOG_NAKED_QUAD
#define LOG_HIDDEN_TRIPLE
//#define LOG_IN_OUT
#define LOG_LINES
#define LOG_NAKED_PAIR
#define LOG_NAKED_TRIPLE
#define LOG_POINTING_LINE
#define LOG_RECTANGLE
#define LOG_REMOVE_CANDIDATE
#define LOG_BOX_LINE
#define LOG_UNIQUE
#define LOG_XY_CHAIN
#define LOG_Y_WING

// Definitions to distinguish between Y-wing and XY-chain when invoking
// pairs_find()
#define DEF_Y_WING  0
#define DEF_XY_CHAIN 1

// Structure and typedef to build chains of cell coordinates.
// It makes possible to develop functions that return lists of cells.
#define MAX_INTER_N 13
typedef struct rc_struct *rc_p_t;
typedef struct rc_struct {
  int row;
  int col;
  rc_p_t next;
  } rc_struct_t;

// Strategy functions
typedef int (*f_ptr_t)(void);
extern f_ptr_t *strat_all[];
extern char **strat_all_names[];
extern int n_strat_all[];
extern int n_levels;

// List of strategies used in a solution
// 0 means 'unique', 40 means 'backtrack'
// Other strategies: (strat level) * 10 + (strat ID within the level)
extern int strats_used[];
extern int n_strats_used;

// Used in some strategies for clarity
#define ROW 0
#define COL 1
#define BOX 2
extern char *unit_names[3];

// Sudoku declarations in sudoku_solver.c
extern char grid[9][9][10];
extern char row[9][9][2];
extern char col[9][9][2];
extern char box[9][9][2];

// Flags
extern int problem_found;
extern int silent;
extern int backtracking;

// Patch because Windows doesn't recognize srandom() and random()
#ifdef __WIN32__
#define srandom srand
#define random rand
#endif

#endif

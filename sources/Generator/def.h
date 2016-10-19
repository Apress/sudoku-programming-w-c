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
#define FALSE  0
#define TRUE   1

// Used in some strategies for clarity
#define ROW 0
#define COL 1
#define BOX 2
extern char *unit_names[3];

// grid declarations
extern char grid[9][9];
extern char row[9][9][2];
extern char col[9][9][2];
extern char box[9][9][2];
extern char solved[9][9];

// Flags
extern int silent;

// Patch because Windows doesn't recognise srandom() and random()
#ifdef __WIN32__
#define srandom srand
#define random rand
#endif

#endif

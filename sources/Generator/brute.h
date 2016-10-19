/* brute.h
 *
 * Solves a Sudoku by brute force
 *
 * See below for the return codes
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#ifndef BRUTE
#define BRUTE

#define BRUTE_SUCCESSFUL  0
#define BRUTE_IMPOSSIBLE -1
#define BRUTE_TIMEOUT    -2

#define BRUTE_MAX_TIME 10

int brute(void);

#endif

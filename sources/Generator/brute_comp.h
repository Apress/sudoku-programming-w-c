/* brute_comp.h
 *
 * Solves a Sudoku by executing brute() and then compares the result with
 * the reference
 *
 * See below for the return codes
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#ifndef BRUTE_COMPARE
#define BRUTE_COMPARE

// If you modify the following list, change brute_comp_err accordingly
#define BRUTE_COMP_OK            0
#define BRUTE_COMP_DIFFERENT     1
#define BRUTE_COMP_TIMEOUT       2
#define BRUTE_COMP_INCONSISTENT  3
#define BRUTE_COMP_IMPOSSIBLE    4
#define BRUTE_COMP_PROBLEM       5

extern const char *brute_comp_err[];

int brute_comp(void);

#endif

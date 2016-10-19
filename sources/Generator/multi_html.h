/* multi_html.h
 *
 * Saves a multi-grid puzzle to disk as a web page.
 * When the suffix is the empty string, it saves the puzzle. Otherwise,
 * it saves the solution.
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#ifndef MULTI_HTML
#define MULTI_HTML

#define N_GRIDS 1

#define PUZ 0
#define SOL 1

extern char multi_string[N_GRIDS][2][82];
extern int overlapping_box[];

void multi_html(int seed, int what);

#endif

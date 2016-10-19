/* rectangle_step.h
 *
 * Rectangle strategy: moving to the next box.
 *
 * Returns 0 if no paths are possible, 1 or more if at least one path is
 * possible, -1 if the search on this cell and candidate should be aborted,
 * and -2 if rectangle should be aborted.
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#ifndef RECTANGLE_STEP
#define RECTANGLE_STEP

int rectangle_step(int[4], int, int, int, int, int, int);

#endif

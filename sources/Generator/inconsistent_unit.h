/* inconsistent_unit.h
 *
 * Checks that there are no repeated solutions within a unit and that all
 * cells have at least a candidate.
 * Returns TRUE if it finds a problem.
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#ifndef INCONSISTENT_UNIT
#define INCONSISTENT_UNIT

int inconsistent_unit(char*, int, char[9][2]);

#endif

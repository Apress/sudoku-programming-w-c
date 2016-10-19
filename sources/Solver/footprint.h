/* footprint.h
 *
 * It returns the list of cells affected by a given cell.
 *
 * The cells affected are those that share either the row, the column, or the
 * box with the given cell.  After eliminating the duplicates, it makes a
 * total of 20 cells.  The function returns the coordinates by rows and then
 * columns, with the lowest row ID first and, within each row, with the lowest
 * column ID first.
 *
 * Parameters:
 *   1: IN, row ID of the cell for which the footprint is to be determined.
 *   2: IN, column ID of the cell for which the footprint is to be determined.
 *   3: IN, pointer to an area of memory large enough to contain the list =
 *          sizeof(struct rc_struct) * 20.
 *
 * Development note:
 *   The chunk of memory in which to store the list is passed in as an argument
 *   to avoid allocating within the function the memory that must then be
 *   released outside the function.
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#ifndef FOOTPRINT
#define FOOTPRINT
#include "def.h"

#define FOOT_N 20

rc_p_t footprint(int p1, int p2, void* p3);

#endif

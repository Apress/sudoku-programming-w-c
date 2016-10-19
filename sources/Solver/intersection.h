/* intersection.h
 *
 * It returns the list of cells affected by two distinct cells or NULL if
 * the intersection is empty.
 * The coordinates are ordered by rows and then by columns, with the lowest
 * row ID first and, within each row, with the lowest column ID first.
 *
 * Two cells can affect different numbers of cells, depending on how their
 * units overlap:
 *   No overlapping: 2 cells, (r1,c2) and (r2,c1).
 *   Line overlapping: 7 cells, (r1,!c1 && !c2) or (!r1 && !r2, c1).
 *   box overlapping: 7 cells, all within the box except the two.
 *   box and line overlapping: 13 cells, all within the box except the
 *       two, plus all within the line except the one within the same box.
 *
 * Parameters:
 *   1: IN, row ID of cell 1.
 *   2: IN, column ID of cell 1.
 *   3: IN, row ID of cell 2.
 *   4: IN, column ID of cell 2.
 *   5: IN, pointer to an area of memory large enough to contain the list =
 *          sizeof(struct rc_struct) * 13.
 *
 * Development note:
 *   The chunk of memory in which to store the list is passed in as an argument
 *   to avoid allocating within the function the memory that must then be
 *   released outside the function.
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#ifndef INTERSECTION
#define INTERSECTION
#include "def.h"

rc_p_t intersection(int p1, int p2, int p3, int p4, void* p5);

#endif

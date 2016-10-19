/* intersection.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "def.h"
#include "footprint.h"
#include "intersection.h"

rc_p_t intersection(int r1, int c1, int r2, int c2, void *mem) {
#ifdef LOG_IN_OUT
  printf("--- intersection (%d,%d) (%d,%d) >>>\n", r1, c1, r2, c2);
#endif

  int cells_found = FALSE;
  rc_p_t retval = (rc_p_t)mem;
  rc_p_t foot1;
  rc_p_t foot2;

  // Allocate the memory for the two footprints
  void *mem_foots = malloc((FOOT_N * sizeof(rc_struct_t)) << 1);
  if (mem_foots != NULL) {
    rc_p_t mem1 = (rc_p_t)mem_foots;
    rc_p_t mem2 = (rc_p_t)(mem_foots + FOOT_N * sizeof(rc_struct_t));

    // Obtain the two footprints
    foot1 = footprint(r1, c1, mem1);
    foot2 = footprint(r2, c2, mem2);
    }
  else {
    printf("*** intersection (%d,%d) (%d,%d): malloc failure\n",
        r1, c1, r2, c2
        );
    exit(EXIT_FAILURE);
    }

  // Build the list of cells common to the two footprints
  rc_p_t p = retval;
  rc_p_t p1 = foot1;
  rc_p_t p_prev = NULL;
  rc_p_t p_temp;
  do {
    rc_p_t p2 = foot2;
    do {
      if (p2->row == p1->row && p2->col == p1->col) {
        cells_found = TRUE;
        p->row = p1->row;
        p->col = p1->col;
        p_prev = p;
        p_temp = p + 1;
        p->next = p_temp;
        p = p_temp;
        }
      p_temp = p2->next;
      p2 = p_temp;
      } while (p2 != NULL);
    p_temp = p1->next;
    p1 = p_temp;
    } while (p1 != NULL);

  // Terminate the chain by clearing the 'next' pointer of the last cell
  p_prev->next = NULL;

  free(mem_foots);

#ifdef LOG_IN_OUT
  printf("<<< intersection(%d,%d) (%d,%d) ---\n", r1, c1, r2, c2);
#endif
  return (cells_found) ? retval : NULL;
  }

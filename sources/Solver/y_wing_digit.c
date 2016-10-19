/* y_wing_digit.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "cleanup_around.h"
#include "def.h"
#include "intersection.h"
#include "pairs_data.h"
#include "remove_candidate.h"
#include "y_wing_digit.h"

int y_wing_digit(int i0) {
#ifdef LOG_IN_OUT
  printf("--- y_wing_digit (%d) >>>\n", i0);
#endif

#define A 0
#define B 1
#define C 2

  int success = FALSE;

  // +-------+
  // | i0+i1 |
  // +-------+-------+
  // | i1+i2 | i2+i0 |
  // +-------+-------+
  int coords[3][3];    // [cell][unit]
  for (int i1 = 1; i1 <= 9; i1++) {
    for (int i1k = 0; i1k < n_x_pairs[i0][i1]; i1k++) {

      // If we arrive here, i0 is paired with i1, and
      // i1k goes through all the pairs of i0 with i1
      coords[A][ROW] = x_pairs[i0][i1][ROW][i1k];
      coords[A][COL] = x_pairs[i0][i1][COL][i1k];
      coords[A][BOX] = x_pairs[i0][i1][BOX][i1k];
      for (int i2 = 1; i2 <= 9; i2++) {
        if (i2 != i0) {
          for (int i2k = 0; i2k < n_x_pairs[i1][i2]; i2k++) {

            // If we arrive here, i1 is paired with i2, and
            // i2k goes through all the pairs of i1 with i2
            coords[B][ROW] = x_pairs[i1][i2][ROW][i2k];
            coords[B][COL] = x_pairs[i1][i2][COL][i2k];
            coords[B][BOX] = x_pairs[i1][i2][BOX][i2k];

            if (i2 > i1 &&
                   (   coords[A][ROW] == coords[B][ROW]
                    || coords[A][COL] == coords[B][COL]
                    || coords[A][BOX] == coords[B][BOX]
                    )
                 ) {
              for (int i3k = 0; i3k < n_x_pairs[i2][i0]; i3k++) {

                // If we arrive here, i2 is paired with i0, and
                // i3k goes through all the pairs of i2 made with i0
                coords[C][ROW] = x_pairs[i2][i0][ROW][i3k];
                coords[C][COL] = x_pairs[i2][i0][COL][i3k];
                coords[C][BOX] = x_pairs[i2][i0][BOX][i3k];

                if (    coords[C][ROW] != coords[A][ROW]
                     && coords[C][COL] != coords[A][COL]
                     && coords[C][BOX] != coords[A][BOX]
                     && (    coords[C][ROW] == coords[B][ROW]
                          || coords[C][COL] == coords[B][COL]
                          || coords[C][BOX] == coords[B][BOX]
                          )
                     ) {
                  int printed = FALSE;
                  void *mem_block = malloc(MAX_INTER_N*sizeof(struct rc_struct));
                  if (mem_block == NULL) {
                    printf("*** y_wing_digit (%d): malloc failure\n", i0);
                    exit(EXIT_FAILURE);
                    }
                  rc_p_t inter = intersection(coords[A][ROW], coords[A][COL],
                      coords[C][ROW], coords[C][COL], mem_block
                      );
                  rc_p_t p = inter;
                  rc_p_t pp = p;
                  while (p != NULL) {
                    int kR = pp->row;
                    int kC = pp->col;
                    char *elem = grid[kR][kC];
                    if (elem[i0]) {
                      success = TRUE;
#ifdef LOG_Y_WING
                      if (!printed && !silent) {
                        printf("y_wing_digit: (%d,%d):%d%d (%d,%d):%d%d"
                            " (%d,%d):%d%d\n",
                            coords[A][ROW], coords[A][COL], i0, i1,
                            coords[B][ROW], coords[B][COL], i1, i2,
                            coords[C][ROW], coords[C][COL], i2, i0
                            );
                        printf("y_wing_digit: intersection of (%d,%d) and"
                            " (%d,%d):", coords[A][ROW], coords[A][COL],
                            coords[C][ROW], coords[C][COL]
                            );
                        rc_p_t p1 = inter;
                        rc_p_t pp1 = p1;
                        do {
                          if (    pp1->row != coords[B][ROW]
                               || pp1->col != coords[B][COL]
                               ) {
                            printf(" (%d,%d)", pp1->row, pp1->col);
                            }
                          p1 = pp1->next;
                          pp1 = p1;
                          } while (p1 != NULL);
                        printf("\n");
                        printed = TRUE;
                        } // if (!printed..
#endif
                      remove_candidate("y_wing_digit", i0, kR, kC);
                      if (grid[kR][kC][0] == 1) {
                        cleanup_around(kR, kC);
                        }
                      } // if (elem[i0]..
                    p = pp->next;
                    pp = p;
                    }

                  free(mem_block);
                  } // if (coords[C][ROW]..
                } // for (int i3k..
              } // if (i2 > i1..
            } // for (int i2k..
          } // if (i2 != i0..
        } // for (int i2..
      } // for (int i1k..
    } // for (int i1..

#ifdef LOG_IN_OUT
  printf("<<< y_wing_digit (%d) ---\n", i0);
#endif
  return success;
  }

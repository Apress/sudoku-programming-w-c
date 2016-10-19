/* xy_chain_step.c
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
#include "xy_chain_step.h"

#define MAX_DEPTH 8

int chain_length;

int xy_chain_step(chain_info_struct_p info, int depth) {
#ifdef LOG_IN_OUT
  printf("--- xy_chain_step (%d) >>>\n", depth);
#endif

  int n_found = 0;
  chain_info_struct_p next = info->next;
  chain_info_struct_p ix_info_p;
  do {
    ix_info_p = next;
    next = ix_info_p->next;
    } while (next != NULL);
  int i0 = info->digit;
  int ix = ix_info_p->digit;

  for (int iy = 1; iy <= 9 && n_found == 0; iy++) {
    for (int ixy = 0; ixy < n_x_pairs[ix][iy] && n_found == 0; ixy++) {

      int kRxy = x_pairs[ix][iy][ROW][ixy];
      if (kRxy < 9) {
        int kCxy = x_pairs[ix][iy][COL][ixy];
        int kBxy = x_pairs[ix][iy][BOX][ixy];
        if (    kRxy == ix_info_p->coords[ROW]
             || kCxy == ix_info_p->coords[COL]
             || kBxy == ix_info_p->coords[BOX]
             ) {
          int found_something_this_time = FALSE;
          if (iy == i0 && depth > 2) {
            int printed = FALSE;
            void *mem_block = malloc(MAX_INTER_N * sizeof(struct rc_struct));
            if (mem_block == NULL) {
              printf("*** xy_chain_step: malloc failure\n");
              exit(EXIT_FAILURE);
              }
            int kR0 = info->coords[ROW];
            int kC0 = info->coords[COL];
            rc_p_t inter = intersection(kR0, kC0, kRxy, kCxy, mem_block);

            // Check whether intersecting cells contain i0 as candidates.
            rc_p_t p = inter;
            rc_p_t pp = p;
            while (p != NULL) {
              int kR = pp->row;
              int kC = pp->col;
              if (kR < 9 && grid[kR][kC][i0]) {
                found_something_this_time = TRUE;
                n_found++;
#ifdef LOG_XY_CHAIN
                if (!printed && !silent) {
                  printf("xy_chain_step: (%d,%d):%d", info->coords[ROW],
                      info->coords[COL], info->digit
                      );
                  next = info->next;
                  printf("%d", next->digit);
                  do {
                    chain_info_struct_p next1 = next->next;
                    if (next1 != NULL) {
                      printf(" (%d,%d):%d%d", next1->coords[ROW],
                          next1->coords[COL], next->digit, next1->digit
                          );
                      }
                    next = next1;
                    } while (next != NULL);
                  printf(" (%d,%d):%d%d\n", kRxy, kCxy, ix, iy);
                  printf("xy_chain_step: intersection of (%d,%d) and (%d,%d):",
                      kR0, kC0, kRxy, kCxy
                      );
                  rc_p_t p = inter;
                  rc_p_t pp = p;
                  do {
                    printf(" (%d,%d)", pp->row, pp->col);
                    p = pp->next;
                    pp = p;
                    } while (p != NULL);
                  printf("\n");
                  printed = TRUE;
                  } // if (!printed..
#endif

                { // Scan the whole chain to determine its length
                  // and update chain_length
                  chain_info_struct_p info1 = info->next;
                  chain_length = 1;
                  do {
                    chain_length++;
                    chain_info_struct_p info2 = info1->next;
                    info1 = info2;
                    } while (info1 != NULL);
                  }

                remove_candidate("xy_chain_step", i0, kR, kC);
                if (grid[kR][kC][0] == 1) {
                  cleanup_around(kR, kC);
                  }
                } // if (elem[i0]..
              p = pp->next;
              pp = p;
              }

            free(mem_block);
            } // if (iy..

          if (!found_something_this_time) {

            // The chain is to be extended
            x_pairs[ix][iy][ROW][ixy] += 10;
            x_pairs[iy][ix][ROW][ixy] += 10;
            chain_info_struct_t iy_info;
            iy_info.digit = iy;
            iy_info.coords[ROW] = kRxy;
            iy_info.coords[COL] = kCxy;
            iy_info.coords[BOX] = kBxy;
            iy_info.next = NULL;
            ix_info_p->next = &iy_info;

            // Keep following the chain
            if (depth < MAX_DEPTH) {
              n_found += xy_chain_step(info, depth + 1);
              }

            // Clean up behind you
            ix_info_p->next = NULL;
            x_pairs[ix][iy][ROW][ixy] -= 10;
            x_pairs[iy][ix][ROW][ixy] -= 10;
            } // if (!found_something_this_time..
          } // if (kRxy ==..
        } // if (kRxy <..
      } // for (int ixy..
    } // for (int iy..

#ifdef LOG_IN_OUT
  printf("<<< xy_chain_step (%d) ---\n", depth);
#endif
  return n_found;
  }

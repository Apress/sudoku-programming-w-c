/* pairs_find.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "def.h"
#include "pairs_data.h"
#include "pairs_find.h"
#include "xy_chain_digit.h"
#include "y_wing_digit.h"

int pairs_find(int chain_type) {
#ifdef LOG_IN_OUT
  printf("--- pairs_find (%d) >>>\n", chain_type);
#endif

  int result = FALSE;

  for (int k = 0; k <= 9; k++) {
    for (int j = 0; j <= 9; j++) {
      n_x_pairs[k][j] = 0;
      }
    }

  // Scan the grid to determine the distribution of pairs across candidates
  for (int k = 0; k < 9; k++) {
    for (int j = 0; j < 9; j++) {
      char *elem = grid[k][j];
      if (elem[0] == 2) {
        int nn[2] = {0, 0};
        int n = 0;
        for (int i = 1; j <= 9 && n < 2; i++) {
          if (elem[i] == TRUE) {
            nn[n] = i;
            n++;
            }
          }
        n_x_pairs[nn[0]][nn[1]]++;
        n_x_pairs[nn[0]][0]++;
        n_x_pairs[nn[1]][nn[0]]++; // let's make the matrix symmetrical...
        n_x_pairs[nn[1]][0]++;     // ...not needed but makes life simpler
        n_x_pairs[0][0]++;         // total count of pairs
        } // if (elem[0]..
      } // for (int j..
    } // for (int k..

  // Allocate space for the lists of row, column, and box IDs.
  // Multiply it by three to save row, column, and box (which is redundant).
  char *data_block = (char*)malloc(n_x_pairs[0][0] * sizeof(char*) * 3);
  if (data_block != NULL) {
    char *offset = data_block;
    for (int i1 = 1; i1 <= 9; i1++) {
      for (int i2 = 1; i2 <= 9; i2++) {
        for (int kkk = 0; kkk < 3; kkk++) {
          x_pairs[i1][i2][kkk] = offset;
          offset += n_x_pairs[i1][i2];
          }
        } // for (int i2..
      } // for (int i1..
    } // if (data_block..
  else {
    printf("*** pairs_find: malloc failure\n");
    exit(EXIT_FAILURE);
    }

  // Clear the pair counters and then populate the pair grid while recounting
  // the pairs
  for (int i1 = 1; i1 <= 9; i1++) {
    for (int i2 = 1; i2 <= 9; i2++) {
      n_x_pairs[i1][i2] = 0;
      }
    }
  for (int k = 0; k < 9; k++) {
    for (int j = 0; j < 9; j++) {
      char *elem = grid[k][j];
      if (elem[0] == 2) {
        int nn[2] = {0, 0};
        int n = 0;
        for (int i = 1; j <= 9 && n < 2; i++) {
          if (elem[i] == TRUE) {
            nn[n] = i;
            n++;
            }
          } // for (int i..
        int i1 = nn[0];
        int i2 = nn[1];
        int np = n_x_pairs[i1][i2];
        n_x_pairs[i1][i2]++;
        n_x_pairs[i2][i1]++;
        x_pairs[i1][i2][ROW][np] = (char)k;
        x_pairs[i1][i2][COL][np] = (char)j;
        x_pairs[i1][i2][BOX][np] = (char)(k/3*3+j/3);
        x_pairs[i2][i1][ROW][np] = (char)k;
        x_pairs[i2][i1][COL][np] = (char)j;
        x_pairs[i2][i1][BOX][np] = (char)(k/3*3+j/3);
        } // if (elem[0]..
      } // for (int j..
    } // for (int k..

  // Go through the digits, but only if they have at least two pairs.
  typedef int (*chain_funct_ptr_t)(int);
  chain_funct_ptr_t chain_functs[] = {y_wing_digit, xy_chain_digit};
  for (int i = 1; i <= 9 && !result; i++) {
    if (n_x_pairs[i][0] >= 2) {
      result |= chain_functs[chain_type](i);
      }
    } // for (int i..

/* Displaying the list of pairs */ /*
  for (int i1 = 1; i1 <= 9; i1++) {
    if (n_x_pairs[i1][0] > 0) {
      printf("\ntotal #pairs for %d: %d\n", i1,
             n_x_pairs[i1][0]
             );
      }
    for (int i2 = 1; i2 <= 9; i2++) {
      if (n_x_pairs[i1][i2] > 0) {
        printf("%d %d [%d]:", i1, i2,
               n_x_pairs[i1][i2]
               );
        for (int kkk = 0;
             kkk < n_x_pairs[i1][i2];
             kkk++
             ) {
          printf(" (%d,%d)", x_pairs[i1][i2][0][kkk],
              x_pairs[i1][i2][1][kkk]
              );
          }
        printf("\n");
        }
      }
    }
*/
  free(data_block);

#ifdef LOG_IN_OUT
  printf("<<< pairs_find (%d) ---\n", chain_type);
#endif
  return result;
  }

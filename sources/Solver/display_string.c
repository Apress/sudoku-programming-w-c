/* display_string.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "def.h"
#include "display_string.h"

void display_string() {
  printf("****** ");
  for (int k = 0; k < 9; k++) {
    for (int j = 0; j < 9; j++) {
      char *elem = grid[k][j];
      if (elem[0] > 1) {
        printf("0");
        }
      else {
        int i = 0;
        do { i++; } while (!elem[i]);
        printf("%d", i);
        }
      }
    }
  printf("\n");
  }

/* display_string.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "def.h"
#include "display_string.h"

void display_string(char *name) {
  for (int k = 0; k < 9; k++) {
    for (int j = 0; j < 9; j++) {
      printf("%d", grid[k][j]);
      }
    }
  if (name != NULL) printf(" \"%s\"", name);
  printf("\n");
  }

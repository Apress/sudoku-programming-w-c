/* display.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "def.h"
#include "display.h"

void display() {
  char *h = "  ++---+---+---++---+---+---++---+---+---++";
  char *hh = "  ++===+===+===++===+===+===++===+===+===++";
  int jBase[] = {2, 6, 10, 15, 19, 23, 28, 32, 36};
  printf("     0   1   2    3   4   5    6   7   8\n");
  for (int k = 0; k < 9; k++) {
    if (k%3 == 0) {
      printf("%s\n", hh);
      }
    else {
      printf("%s\n", h);
      }
    //                000 000 111  111 122 222  223 333 333
    //                234 678 012  567 901 345  890 234 678
    char top[42] = "||   |   |   ||   |   |   ||   |   |   ||";
    char mid[42] = "||   |   |   ||   |   |   ||   |   |   ||";
    char bot[42] = "||   |   |   ||   |   |   ||   |   |   ||";
    char *displ[42] = {top, mid, bot};
    for (int j = 0; j < 9; j++) {
      if (grid[k][j] == 0) {
        mid[jBase[j]+1] = ' ';
        }
      else {
        mid[jBase[j]+1] = '0' + grid[k][j];
        }
      } // for (int j..
    printf("  %s\n", displ[0]);
    printf("%d %s\n", k, displ[1]);
    printf("  %s\n", displ[2]);
    }
  printf("%s\n", hh);
  }

/* lines_4.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "def.h"
#include "lines.h"
#include "lines_4.h"

int lines_4() {
#ifdef LOG_IN_OUT
  printf("--- lines_4 >>>\n");
#endif
  int result = FALSE;
  char comb[4];

  // Try all 9*8*7*6 / 4! = 126 combinations
  for (int kRC = 0; kRC < 2 && !result; kRC++) {
    for (int k1 = 0; k1 < 6 && !result; k1++) {
      for (int k2 = k1+1; k2 < 7 && !result; k2++) {
        for (int k3 = k2+1; k3 < 8 && !result; k3++) {
          for (int k4 = k3+1; k4 < 9 && !result; k4++) {
            comb[0] = k1;
            comb[1] = k2;
            comb[2] = k3;
            comb[3] = k4;
            for (int i = 1; i <= 9 && !result; i++) {
              result |= lines(kRC, comb, 4, i);
              }
            } // for (int k4..
          } // for (int k3..
        } // for (int k2..
      } // for (int k1..
    } // for int kRC..
#ifdef LOG_IN_OUT
  printf("<<< lines_4 ---\n");
#endif
  return result;
  }

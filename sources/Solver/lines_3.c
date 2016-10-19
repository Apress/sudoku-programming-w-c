/* lines_3.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "def.h"
#include "lines.h"
#include "lines_3.h"

int lines_3() {
#ifdef LOG_IN_OUT
  printf("--- lines_3 >>>\n");
#endif
  int result = FALSE;
  char comb[3];

  // Try all 9*8*7 / 3! = 84 combinations
  for (int kRC = 0; kRC < 2 && !result; kRC++) {
    for (int k1 = 0; k1 < 7 && !result; k1++) {
      for (int k2 = k1+1; k2 < 8 && !result; k2++) {
        for (int k3 = k2+1; k3 < 9 && !result; k3++) {
          comb[0] = k1;
          comb[1] = k2;
          comb[2] = k3;
          for (int i = 1; i <= 9 && !result; i++) {
            result |= lines(kRC, comb, 3, i);
            }
          } // for (int k3..
        } // for (int k2..
      } // for (int k1..
    } // for int kRC..
#ifdef LOG_IN_OUT
  printf("<<< lines_3 ---\n");
#endif
  return result;
  }

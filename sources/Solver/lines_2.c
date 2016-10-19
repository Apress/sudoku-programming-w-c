/* lines_2.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "def.h"
#include "lines.h"
#include "lines_2.h"

int lines_2() {
#ifdef LOG_IN_OUT
  printf("--- lines_2 >>>\n");
#endif
  int result = FALSE;
  char comb[2];

  // Try all 9*8 / 2! = 36 combinations
  for (int kRC = 0; kRC < 2 && !result; kRC++) {
    for (int k1 = 0; k1 < 8 && !result; k1++) {
      for (int k2 = k1+1; k2 < 9 && !result; k2++) {
        comb[0] = k1;
        comb[1] = k2;
        for (int i = 1; i <= 9 && !result; i++) {
          result |= lines(kRC, comb, 2, i);
          }
        } // for (int k2..
      } // for (int k1..
    } // for int kRC..
#ifdef LOG_IN_OUT
  printf("<<< lines_2 ---\n");
#endif
  return result;
  }

/* in_box.c
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "in_box.h"

int in_box(int kR, int kC, int kB) {
  int kkR = kB / 3 * 3;
  int kkC = kB % 3 * 3;
  return (kR >= kkR  &&  kR < kkR + 3  &&  kC >= kkC  &&  kC < kkC + 3);
  } // in_box

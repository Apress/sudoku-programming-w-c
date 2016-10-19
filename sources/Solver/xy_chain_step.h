/* xy_chain_step.h
 *
 * XY-chain strategy: moving along the chain till the end.
 *
 * Returns the number of candidates removed.
 *
 * Copyright (C) 2015  Giulio Zambon  - http://zambon.com.au/
 *
 */
#ifndef XY_CHAIN_STEP
#define XY_CHAIN_STEP

typedef struct chain_info_struct *chain_info_struct_p;
typedef struct chain_info_struct {
  int digit;
  int coords[3];
  chain_info_struct_p next;
  } chain_info_struct_t;

extern int chain_length;

int xy_chain_step(chain_info_struct_p, int);

#endif

#include "header.h"

unsigned int op1[16384];
unsigned int op2[16384];

__attribute__((noinline))
void example9 (unsigned *ret) {
  int i;

  /* feature: support summation reduction.
     note: in case of floats use -funsafe-math-optimizations  */
  unsigned int sum_sub = 0;
  for (i = 0; i < 16384; i++) {
    sum_sub += (op1[i] -op2[i]);
  }

  *ret = sum_sub;
}

int main(int argc,char* argv[]){
  unsigned dummy = 0;
  init_memory(&op1[0], &op1[16384]);
  init_memory(&op2[0], &op2[16384]);
  BENCH("Example9",   example9(&dummy), Mi*4/16384*512, dummy);
 
  return 0;
}

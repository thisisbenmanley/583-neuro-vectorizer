#include "header.h"

int   ia[4096] ALIGNED16;
int op1[256][4096];
int op2[256][4096];

__attribute__((noinline))
void example13(int op1[][4096], int op2[][4096], int *out) {
  int i,j;
  for (i = 0; i < 256; i++) {
    int sum_sub = 0;
    for (j = 0; j < 4096; j+=8) {
      sum_sub += (op1[i][j] -op2[i][j]);
    }
    out[i] = sum_sub;
  }
}
int main(int argc,char* argv[]){
  init_memory(&ia[0], &ia[4096]);
  init_memory(&op1[0][0], &op1[0][4096]);
  init_memory(&op2[0][0],&op2[0][4096]);
  BENCH("Example13",  example13(op1,op2,ia), 2048, digest_memory(&ia[0], &ia[4096]));
  return 0;
}

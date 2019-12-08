#include "header.h"

int   ia[64] ALIGNED16;
int op1[4096][64];
int op2[4096][64];

__attribute__((noinline))
void example13(int op1[][64], int op2[][64], int *out) {
  int i,j;
  for (i = 0; i < 4096; i++) {
    int sum_sub = 0;
    for (j = 0; j < 64; j+=8) {
      sum_sub += (op1[i][j] -op2[i][j]);
    }
    out[i] = sum_sub;
  }
}
int main(int argc,char* argv[]){
  init_memory(&ia[0], &ia[64]);
  init_memory(&op1[0][0], &op1[0][64]);
  init_memory(&op2[0][0],&op2[0][64]);
  BENCH("Example13",  example13(op1,op2,ia), 8192, digest_memory(&ia[0], &ia[64]));
  return 0;
}

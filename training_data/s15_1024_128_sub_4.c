#include "header.h"

int   ia[128] ALIGNED16;
int op1[1024][128];
int op2[1024][128];

__attribute__((noinline))
void example13(int op1[][128], int op2[][128], int *out) {
  int i,j;
  for (i = 0; i < 1024; i++) {
    int sum_sub = 0;
    for (j = 0; j < 128; j+=8) {
      sum_sub += (op1[i][j] -op2[i][j]);
    }
    out[i] = sum_sub;
  }
}
int main(int argc,char* argv[]){
  init_memory(&ia[0], &ia[128]);
  init_memory(&op1[0][0], &op1[0][128]);
  init_memory(&op2[0][0],&op2[0][128]);
  BENCH("Example13",  example13(op1,op2,ia), 16384, digest_memory(&ia[0], &ia[128]));
  return 0;
}

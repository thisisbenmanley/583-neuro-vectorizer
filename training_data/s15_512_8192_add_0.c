#include "header.h"

int   ia[8192] ALIGNED16;
int A[512][8192];
int B[512][8192];

__attribute__((noinline))
void example13(int A[][8192], int B[][8192], int *out) {
  int i,j;
  for (i = 0; i < 512; i++) {
    int add = 0;
    for (j = 0; j < 8192; j+=8) {
      add += (A[i][j] +B[i][j]);
    }
    out[i] = add;
  }
}
int main(int argc,char* argv[]){
  init_memory(&ia[0], &ia[8192]);
  init_memory(&A[0][0], &A[0][8192]);
  init_memory(&B[0][0],&B[0][8192]);
  BENCH("Example13",  example13(A,B,ia), 512, digest_memory(&ia[0], &ia[8192]));
  return 0;
}

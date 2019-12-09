#include "header.h"

int   ia[8];
int G[1024][2048];
int G2[1024+8][2048];

__attribute__((noinline))
void example14(int A[][2048], int coeff[][2048], int *out) {
  int k,j,i=0;
  for (k = 0; k < 8; k++) {
    int sum = 0;
    for (i = 0; i < 1024; i++)
        for (j = 0; j < 2048; j++)
          sum += A[i+k][j] * coeff[i][j];

    out[k] = sum;
  }
}

int main(int argc,char* argv[]){
  init_memory(&ia[0], &ia[8]);
  init_memory(&G[0][0], &G[0][2048]);
  init_memory(&G2[0][0],&G2[0][2048]);
  BENCH("Example14",  example14(G2,G,ia), 128, digest_memory(&ia[0], &ia[8]));
  return 0;
}

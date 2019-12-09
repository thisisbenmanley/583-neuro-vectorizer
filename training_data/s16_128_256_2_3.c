#include "header.h"

int   ia[2];
int G[128][256];
int G2[128+2][256];

__attribute__((noinline))
void example14(int A[][256], int coeff[][256], int *out) {
  int k,j,i=0;
  for (k = 0; k < 2; k++) {
    int sum = 0;
    for (i = 0; i < 128; i++)
        for (j = 0; j < 256; j++)
          sum += A[i+k][j] * coeff[i][j];

    out[k] = sum;
  }
}

int main(int argc,char* argv[]){
  init_memory(&ia[0], &ia[2]);
  init_memory(&G[0][0], &G[0][256]);
  init_memory(&G2[0][0],&G2[0][256]);
  BENCH("Example14",  example14(G2,G,ia), 32768, digest_memory(&ia[0], &ia[2]));
  return 0;
}

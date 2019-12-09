#include "header.h"

int   ia[8];
int G[1024][16384];
int G2[1024+8][16384];

__attribute__((noinline))
void example14(int in[][16384], int coeff[][16384], int *result) {
  int k,j,i=0;
  for (k = 0; k < 8; k++) {
    int sum = 0;
    for (i = 0; i < 1024; i++)
        for (j = 0; j < 16384; j++)
          sum += in[i+k][j] * coeff[i][j];

    result[k] = sum;
  }
}

int main(int argc,char* argv[]){
  init_memory(&ia[0], &ia[8]);
  init_memory(&G[0][0], &G[0][16384]);
  init_memory(&G2[0][0],&G2[0][16384]);
  BENCH("Example14",  example14(G2,G,ia), 16, digest_memory(&ia[0], &ia[8]));
  return 0;
}

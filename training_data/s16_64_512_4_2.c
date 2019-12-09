#include "header.h"

int   ia[4];
int G[64][512];
int G2[64+4][512];

__attribute__((noinline))
void example14(int in[][512], int coeff[][512], int *result) {
  int k,j,i=0;
  for (k = 0; k < 4; k++) {
    int sum = 0;
    for (i = 0; i < 64; i++)
        for (j = 0; j < 512; j++)
          sum += in[i+k][j] * coeff[i][j];

    result[k] = sum;
  }
}

int main(int argc,char* argv[]){
  init_memory(&ia[0], &ia[4]);
  init_memory(&G[0][0], &G[0][512]);
  init_memory(&G2[0][0],&G2[0][512]);
  BENCH("Example14",  example14(G2,G,ia), 16384, digest_memory(&ia[0], &ia[4]));
  return 0;
}

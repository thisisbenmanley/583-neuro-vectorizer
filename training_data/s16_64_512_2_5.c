#include "header.h"

int   ia[2];
int G[64][512];
int G2[64+2][512];

__attribute__((noinline))
void example14(int mat1[][512], int mat2[][512], int *out) {
  int k,j,i=0;
  for (k = 0; k < 2; k++) {
    int sum = 0;
    for (i = 0; i < 64; i++)
        for (j = 0; j < 512; j++)
          sum += mat1[i+k][j] * mat2[i][j];

    out[k] = sum;
  }
}

int main(int argc,char* argv[]){
  init_memory(&ia[0], &ia[2]);
  init_memory(&G[0][0], &G[0][512]);
  init_memory(&G2[0][0],&G2[0][512]);
  BENCH("Example14",  example14(G2,G,ia), 32768, digest_memory(&ia[0], &ia[2]));
  return 0;
}

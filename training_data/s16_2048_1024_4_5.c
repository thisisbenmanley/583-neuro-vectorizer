#include "header.h"

int   ia[4];
int G[2048][1024];
int G2[2048+4][1024];

__attribute__((noinline))
void example14(int mat1[][1024], int mat2[][1024], int *out) {
  int k,j,i=0;
  for (k = 0; k < 4; k++) {
    int sum = 0;
    for (i = 0; i < 2048; i++)
        for (j = 0; j < 1024; j++)
          sum += mat1[i+k][j] * mat2[i][j];

    out[k] = sum;
  }
}

int main(int argc,char* argv[]){
  init_memory(&ia[0], &ia[4]);
  init_memory(&G[0][0], &G[0][1024]);
  init_memory(&G2[0][0],&G2[0][1024]);
  BENCH("Example14",  example14(G2,G,ia), 256, digest_memory(&ia[0], &ia[4]));
  return 0;
}

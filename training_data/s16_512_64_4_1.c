#include "header.h"

int   ia[4];
int G[512][64];
int G2[512+4][64];

__attribute__((noinline))
void example14(int in[][64], int coeff[][64], int *out) {
  int k,j,i=0;
  for (k = 0; k < 4; k++) {
    int result = 0;
    for (i = 0; i < 512; i++)
        for (j = 0; j < 64; j++)
          result += in[i+k][j] * coeff[i][j];

    out[k] = result;
  }
}

int main(int argc,char* argv[]){
  init_memory(&ia[0], &ia[4]);
  init_memory(&G[0][0], &G[0][64]);
  init_memory(&G2[0][0],&G2[0][64]);
  BENCH("Example14",  example14(G2,G,ia), 16384, digest_memory(&ia[0], &ia[4]));
  return 0;
}
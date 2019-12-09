#include "header.h"

int   ia[8];
int G[16384][512];
int G2[16384+8][512];

__attribute__((noinline))
void example14(int in[][512], int coeff[][512], int *out) {
  int k,j,i=0;
  for (k = 0; k < 8; k++) {
    int result = 0;
    for (i = 0; i < 16384; i++)
        for (j = 0; j < 512; j++)
          result += in[i+k][j] * coeff[i][j];

    out[k] = result;
  }
}

int main(int argc,char* argv[]){
  init_memory(&ia[0], &ia[8]);
  init_memory(&G[0][0], &G[0][512]);
  init_memory(&G2[0][0],&G2[0][512]);
  BENCH("Example14",  example14(G2,G,ia), 32, digest_memory(&ia[0], &ia[8]));
  return 0;
}

#include "header.h"

int   ia[2];
int G[1024][128];
int G2[1024+2][128];

__attribute__((noinline))
void example14(int in[][128], int coeff[][128], int *out) {
  int k,j,i=0;
  for (k = 0; k < 2; k++) {
    int result = 0;
    for (i = 0; i < 1024; i++)
        for (j = 0; j < 128; j++)
          result += in[i+k][j] * coeff[i][j];

    out[k] = result;
  }
}

int main(int argc,char* argv[]){
  init_memory(&ia[0], &ia[2]);
  init_memory(&G[0][0], &G[0][128]);
  init_memory(&G2[0][0],&G2[0][128]);
  BENCH("Example14",  example14(G2,G,ia), 8192, digest_memory(&ia[0], &ia[2]));
  return 0;
}

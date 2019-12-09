#include "header.h"

int   ia[8];
int G[8192][256];
int G2[8192+8][256];

__attribute__((noinline))
void example14(int in[][256], int coeff[][256], int *out) {
  int k,j,i=0;
  for (k = 0; k < 8; k++) {
    int dot_product = 0;
    for (i = 0; i < 8192; i++)
        for (j = 0; j < 256; j++)
          dot_product += in[i+k][j] * coeff[i][j];

    out[k] = dot_product;
  }
}

int main(int argc,char* argv[]){
  init_memory(&ia[0], &ia[8]);
  init_memory(&G[0][0], &G[0][256]);
  init_memory(&G2[0][0],&G2[0][256]);
  BENCH("Example14",  example14(G2,G,ia), 128, digest_memory(&ia[0], &ia[8]));
  return 0;
}

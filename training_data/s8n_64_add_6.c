#include "header.h"

int sum[64] ALIGNED16;
int in[64] ALIGNED16;

__attribute__((noinline))
void  example7 (int x) {
   int i;

   /* feature: support for read accesses with an unknown misalignment  */
   for (i=0; i<64-x; i++){
      sum[i] += in[i+x];
   }
}

int main(int argc,char* argv[]){
  init_memory(&sum[0], &sum[64]);
  init_memory(&in[0], &in[64]);
 
  BENCH("Example7",   example7(4), Mi/64*512, digest_memory(&sum[0], &sum[64]));
  return 0;
}

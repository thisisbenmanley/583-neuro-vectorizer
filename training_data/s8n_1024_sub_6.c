#include "header.h"

int sum[1024] ALIGNED16;
int in[1024] ALIGNED16;

__attribute__((noinline))
void  example7 (int x) {
   int i;

   /* feature: support for read accesses with an unknown misalignment  */
   for (i=0; i<1024-x; i++){
      sum[i] -= in[i+x];
   }
}

int main(int argc,char* argv[]){
  init_memory(&sum[0], &sum[1024]);
  init_memory(&in[0], &in[1024]);
 
  BENCH("Example7",   example7(4), Mi/1024*512, digest_memory(&sum[0], &sum[1024]));
  return 0;
}

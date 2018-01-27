#include <stdio.h>
#include <stdlib.h>
#include "lfsr.h"

void Berlekamp(maxlen_t * res, int * periode, maxlen_t poly, int n){

	maxlen_t P=1;
	maxlen_t Q=1;
	int lambda=0;
	int m=-1;
	maxlen_t T;
	int k=0;
	int i=0;
	int d;
	
	for(k=0; k<n; k++){
		d=0;
		
		for(i=0; i<=lambda; i++){
			d^=((P>>i)&1)&((poly>>(k-i))&1);
		}
		if(d==1){
			T=P;
			P^=(Q<<(k-m));
			if(lambda<=(k>>1)){
				lambda=k+1-lambda;
				m=k;
				Q=T;
			
			}
		
		
		}
			
	
	}
	*res=P;
	*periode=lambda;
	return;

}


int main(){

maxlen_t res;
int periode;
maxlen_t entree= 0b110010110101;   

Berlekamp(&res, &periode, entree, 12);

fprintf(stdout, "res: %lx  periode: %d \n", res, periode);
return 1;


}









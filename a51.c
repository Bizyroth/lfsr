#include "lfsr.h"
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
byte_t horloge(lfsr_t lfsr, int num){

	if(num==1){
		return (((lfsr.cont)->regist)>>7)&1;
	}
	else if(num==2){
		return (((lfsr.cont)->regist)>>27)&1;
	}
	else{
		return (((lfsr.cont)->regist)>>48)&1;
	}

}

maxlen_t strtohex(char * s){
	maxlen_t res=0ULL;
	int i=0;
	for(i=0; i< strlen(s); i++){
		switch(s[strlen(s)-1-i]){
		
			case '0':
				res|=(maxlen_t)(0b0000)<<(i*4);
				break;
			case '1':
				res|=(maxlen_t)(0b0001)<<(i*4);
				break;	
			case '2':
				res|=(maxlen_t)(0b0010)<<(i*4);
				break;
			case '3':
				res|=(maxlen_t)(0b0011)<<(i*4);
				break;
			case '4':
				res|=(maxlen_t)(0b0100)<<(i*4);
				break;
			case '5':
				res|=(maxlen_t)(0b0101)<<(i*4);
				break;
			case '6':
				res|=(maxlen_t)(0b0110)<<(i*4);
				break;
			case '7':
				res|=(maxlen_t)(0b0111)<<(i*4);
				break;
			case '8':
				res|=(maxlen_t)(0b1000)<<(i*4);
				break;
			case '9':
				res|=(maxlen_t)(0b1001)<<(i*4);
				break;
			case 'a':
				res|=(maxlen_t)(0b1010)<<(i*4);
				break;
			case 'b':
				res|=(maxlen_t)(0b1011)<<(i*4);
				break;
			case 'c':
				res|=(maxlen_t)(0b1100)<<(i*4);
				break;
			case 'd':
				res|=(maxlen_t)(0b1101)<<(i*4);
				break;
			case 'e':
				res|=(maxlen_t)(0b1110)<<(i*4);
				break;
			case 'f':
				res|=(maxlen_t)(0b1111)<<(i*4);
		
			default:
				break;
	
		}
	}
	return res;

}


int main(int argc, char * argv[]){

	lfsr_t lfsr1, lfsr2, lfsr3;
	container_t contain;
	byte_t b1=0, b2=0, b3=0;
	int i=0;
	maxlen_t reg;
	
	if(argc!=2){
		fprintf(stdout,"Vous pouvez passer le registre d'initialisation en argument\n");
		fprintf(stdout, "./a51 reg avec reg (EN HEXADECIMAL)\n");
		reg=0x1234567abcdef;
		fprintf(stdout, "Voici quand meme un exemple avec 0x1234567abcdef comme initialisation\n");
	}
	else{
		reg=strtohex(argv[1]);
	}	
	
	
	//P3P2P1	
	lfsr_container_init(&contain, reg ,0xe001018000072000); 
	lfsr_init(&lfsr3,  0, 23, &contain);
	lfsr_init(&lfsr2, 23, 22, &contain);
	lfsr_init(&lfsr1, 45, 19, &contain);
	
	
		
	for(i=0; i<255; i++){
	
		if((horloge(lfsr1, 1)==0 && horloge(lfsr2, 2)==0 && horloge(lfsr3, 3)==0) ||
			(horloge(lfsr1, 1)==1 && horloge(lfsr2, 2)==1 && horloge(lfsr3, 3)==1)){
		
			b1=lfsr_inc(&lfsr1);
			b2=lfsr_inc(&lfsr2);
			b3=lfsr_inc(&lfsr3);
		
		}
		else if( (horloge(lfsr1, 1)==0 && horloge(lfsr2, 2)==0 && horloge(lfsr3, 3)==1) ||
			(horloge(lfsr1, 1)==1 && horloge(lfsr2, 2)==1 && horloge(lfsr3, 3)==0)){
		
			b1=lfsr_inc(&lfsr1);
			b2=lfsr_inc(&lfsr2);
		}
		else if( (horloge(lfsr1, 1)==0 && horloge(lfsr2, 2)==1 && horloge(lfsr3, 3)==0) ||
			(horloge(lfsr1, 1)==1 && horloge(lfsr2, 2)==0 && horloge(lfsr3, 3)==1)){
	
			b1=lfsr_inc(&lfsr1);
			b3=lfsr_inc(&lfsr3);
		}
		else{
	
			b2=lfsr_inc(&lfsr2);
			b3=lfsr_inc(&lfsr3);
		}
	
		fprintf(stdout, "%d", b1^b2^b3);
	
	}
	fprintf(stdout, "\n");
	
	return 0;

}

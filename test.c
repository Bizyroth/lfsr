#include <stdio.h>
#include <stdlib.h>
#include "lfsr.h"
#include <string.h>
#include <inttypes.h>

int main(int argc , char * argv[]){
	
	int i=0;
	container_t cont;
	lfsr_t lfsr;
	byte_t sortie;
	
	if(argc==2 && strcmp(argv[1],"test")==0){
		lfsr_container_init(&cont, 0x80808080, 0x71717171);
		
		lfsr_init(&lfsr, 56, 8, &cont);
		
		for(i=0; i<256; i++){
			printf("lfr: %d   ", i);
			affiche_lfsr(&lfsr);
			sortie=lfsr_inc(&lfsr);
			fprintf(stdout, "sortie: %d\n", sortie);
		}
		return 1;
	}

	else if(argc==1){
	
		fprintf(stdout, "------------------------------------LFSR-------------------------------------\n\n");
		fprintf(stdout, "Veuillez entrer le nombre de LFSR que vous souhaitez mettre dans votre registre\n\n");
		int nbr_lfsr;
		int j=0;
		maxlen_t r=0;
		maxlen_t p=0;
		byte_t z=0;
		byte_t l=0;
		container_t contain;
		maxlen_t reg_final=0;
		maxlen_t poly_final=0;
		scanf("%d", &nbr_lfsr);
		
		if((nbr_lfsr>MAXLEN) || (nbr_lfsr<=0)){
			fprintf(stderr, "Veuillez entrer un d coherent\n");
			fprintf(stderr, "d>0 et d< %lx\n", MAXLEN);
			return 0;
		}
		
		lfsr_t table[nbr_lfsr];
		
		while(i<nbr_lfsr){
			fprintf(stdout, "|---------------------------LFSR No %d-------------------------|\n",i+1);
			fprintf(stdout, "|                                                              |\n");
			fprintf(stdout, "|--------------Entrez le registre du LFSR (en hexa)------------|\n");
			fprintf(stdout, "                             ");
			scanf("%lx", &r);
			fprintf(stdout, "|                                                              |\n");
			fprintf(stdout, "|----------------Entrez le polynome (en hexa)------------------|\n");
			fprintf(stdout, "                             ");
			scanf("%lx", &p);
			fprintf(stdout, "|                                                              |\n");
			fprintf(stdout, "|-------------Entrez la position de depart du registre---------|\n");
			fprintf(stdout, "                             ");
			scanf("%"SCNu8, &z);
			fprintf(stdout, "|                                                              |\n");
			fprintf(stdout, "|--------------Entrez la longueur du registre------------------|\n");
			fprintf(stdout, "                             ");
			scanf("%"SCNu8, &l); 
			fprintf(stdout, "|                                                              |\n");
			reg_final^=(r<<(MAXLEN-(z+l)));
			poly_final^=(p<<(MAXLEN-(z+l)));
			lfsr_init(&(table[i]), z, l, &contain);
			i++;			

		}
		
		lfsr_container_init(&contain, reg_final, poly_final);
		
		
	
		for(i=0; i<255; i++){
			for(j=0;j<nbr_lfsr;j++){	
				printf("lfsr %d  ", j+1);
				affiche_lfsr(&table[j]);
				sortie=lfsr_inc(&table[j]);
				fprintf(stdout, "sortie : %d\n", sortie);
			}
		
		}
		return 1;
	}
	
	else{
		fprintf(stdout," usage ./lfsr test pour avoir un exemple d'excution avec:\n");
		fprintf(stdout," r=80, p=71, z=56 et l=8\n");
		
		fprintf(stdout, "Ou taper ./lfsr et laissez vous guider!!!\n");
		
		return 0;
	}
	 
	
}

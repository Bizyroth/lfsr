#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint8_t byte_t;

#define WITH_64BITS

#if defined(WITH_8BITS)
typedef uint8_t maxlen_t;
#define MAXINT 0xff
#elif defined(WITH_16BITS)
typedef uint16_t maxlen_t;
#define MAXINT 0xffff
#elif defined(WITH_32BITS)
typedef uint32_t maxlen_t;
#define MAXINT 0xffffffff
#elif defined(WITH_64BITS)
typedef uint64_t maxlen_t;
#define MAXINT 0xffffffffffffffffULL
#else
#error("Erreur : taille du registre non définie.")
#endif

/* MAXLEN : constante = longueur maximale, *en bits*, d'un registre. */
#define MAXLEN (sizeof(maxlen_t)<<3)

typedef struct {
  maxlen_t regist;
  maxlen_t poly;
}container_t;

typedef struct { 
  byte_t zero; // position du premier bit du registre (numérotée à partir de 0
  byte_t len;  // longueur du registre
  container_t *cont;
}lfsr_t;

#define MASK(a,b) (MAXINT>>a)&(MAXINT << (MAXLEN-(a+b)) )

#define LFSR_MASK(lfsr) MASK(lfsr->zero, lfsr->len)



void affiche_lfsr(lfsr_t * lfsr){
	
	byte_t a=lfsr->zero;
	byte_t b=lfsr->len;
	
	
	fprintf(stdout, "registre:         %2lx, poly: %lx\n", 
	(maxlen_t)((LFSR_MASK(lfsr)&((lfsr->cont)->regist))>>(MAXLEN-(a+b))), 
	(maxlen_t)((LFSR_MASK(lfsr)&((lfsr->cont)->poly))>>(MAXLEN-(a+b))));	



}

/* Initialisation du conteneur, ne dépend pas de la taille du lfsr, un
   même conteneur peut contenir les registres de plusieurs lfsr. */
int lfsr_container_init (container_t * cont, const maxlen_t t_regist, maxlen_t t_poly){
	
	cont->regist=t_regist;
	cont->poly=t_poly;
	return 1;
}



/* La fonction lfsr__init(lfsr, zero, len, cont)
initialise le lfsr, et vérifie que les données sont cohérentes ;
zero <= MAXLEN
len <= MAXLEN
zero+len-1<=MAXLEN
 */
int lfsr_init (lfsr_t * lfsr, const byte_t t_zero, const byte_t t_len, container_t * contain){
	if((t_zero>=MAXLEN) || (t_len>=MAXLEN) || (t_len + t_zero -1)>=MAXLEN){
		printf("MAXLEN = %lu \n", MAXLEN);
		printf("Erreur d'initailisation\n");
		return 0;
	}
	
	lfsr->zero=t_zero;
	lfsr->len=t_len;
	lfsr->cont=contain;
	return 1;
}



/* Incrémentation du LFSR, ne modifie *que* les bits affectés au LFSR */
byte_t lfsr_inc (lfsr_t * lfsr){
	byte_t a=lfsr->zero;
	byte_t b=lfsr->len;

	maxlen_t new_register=((lfsr->cont)->regist)&LFSR_MASK(lfsr);
	maxlen_t new_poly=((lfsr->cont)->poly)&LFSR_MASK(lfsr);
	
	byte_t bs= ((new_register)>>(MAXLEN-(a+b))) & 1;
		
	maxlen_t temp=new_register & new_poly; 
	
	
	maxlen_t pair=0;
	while(temp!=0){
		pair^=(temp&1);
		temp>>=1;
	}
	
	new_register>>=1;
	new_register&=LFSR_MASK(lfsr);
	new_register^=(pair<<(MAXLEN-a-1));
	
	if((a+b)!=MAXLEN){
		if(a!=0){
			(lfsr->cont)->regist=
			(MASK(0,a) & ((lfsr->cont)->regist)) ^ 
			new_register ^ 
			(MASK((a+b),MAXLEN-(a+b)) &((lfsr->cont)->regist));
		}
		else{
		(lfsr->cont)->regist=new_register ^ 
			(MASK((a+b),MAXLEN-(a+b)) &((lfsr->cont)->regist));

		}
	}

	else{
		(lfsr->cont)->regist=
		(MASK(0,a) & ((lfsr->cont)->regist)) ^ 
		new_register;
	}
	
	return bs;

}




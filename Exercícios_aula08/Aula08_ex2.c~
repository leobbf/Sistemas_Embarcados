#include <stdio.h>
#include <fcntl.h>	// Para a funcao open()
#include <unistd.h>	// Para a funcao close()
#include <stdlib.h>	// Para a função exit()
#include <string.h> // Para funções com string
#include <sys/types.h> //para função system()
#include <signal.h> //para sinais
#include <pthread.h> // para thread 
#include <time.h> //para função time(NULL)


	long int valores_max_global[5];

void *v1(void *v){
	
	long int *valor = (long int *) v;
	int i;

	valores_max_global[0] = valor[0];

		for(i=0; i<12500; i++){

			if(valores_max_global[0]  < valor[i]){
				valores_max_global[0] = valor[i];
			}
		}

}

void *v2(void *v){
	
	long int *valor = (long int *) v;
	int i;

	valores_max_global[1] = valor[12500];

		for(i=12500; i<25000; i++){

			if(valores_max_global[1] < valor[i]){
				valores_max_global[1] = valor[i];
			}
		}

}

void *v3(void *v){
	
	long int *valor = (long int *) v;
	int i;

	valores_max_global[2] = valor[25000];

		for(i=25000; i<37500; i++){

			if(valores_max_global[2]  < valor[i]){
				valores_max_global[2]  = valor[i];
			}
		}
}

void *v4(void *v){

	long int *valor = (long int *) v;
	int i;

	valores_max_global[3] = valor[37500];

		for(i=37500; i<50000; i++){

			if(valores_max_global[3] < valor[i]){
				valores_max_global[3] = valor[i];
			}
		}
}

void *v5(void *v){
	
	long int *valor = (long int *) v;
	int i;

	valores_max_global[4] = valor[0];

		for(i=0; i<50000; i++){

			if(valores_max_global[4] < valor[i]){
				valores_max_global[4] = valor[i];
			}
		}
}

int main(int argc, char **argv){

	pthread_t thread_v1;
	pthread_t thread_v2;
	pthread_t thread_v3;
	pthread_t thread_v4;
	pthread_t thread_v5;

	long int v[50000];
	long int valor_max;	
	int i;

	srand(time(NULL));
	//preenchendo o vetor v
	for(i=0; i<50000; i++){
		
		v[i] = rand();
		//printf("%ld\n", v[i]);
	}
	
	pthread_create(&thread_v1, NULL, &v1, v);
	pthread_create(&thread_v2, NULL, &v2, v);
	pthread_create(&thread_v3, NULL, &v3, v);
	pthread_create(&thread_v4, NULL, &v4, v);
	pthread_create(&thread_v5, NULL, &v5, v);

	pthread_join(thread_v1, NULL);
	pthread_join(thread_v2, NULL);
	pthread_join(thread_v3, NULL);
	pthread_join(thread_v4, NULL);
	pthread_join(thread_v5, NULL);

	valor_max = valores_max_global[0];
	for(i=0; i<4; i++){
		
		if(valor_max < valores_max_global[i]){
			valor_max = valores_max_global[i];
		}

	}

	printf("Valor maximo por busca dividida: %ld\n", valor_max);
	printf("valor maximo por busca completa: %ld\n", valores_max_global[4]);
	

return 0; 
}

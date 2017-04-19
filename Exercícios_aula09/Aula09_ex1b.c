#include <stdio.h>
#include <fcntl.h>	// Para a funcao open()
#include <unistd.h>	// Para a funcao close()
#include <stdlib.h>	// Para a função exit()
#include <string.h> // Para funções com string
#include <sys/types.h> //para função system()
#include <signal.h> //para sinais
#include <pthread.h> // para thread 
#include <time.h> //para função time(NULL)

#define linha 60
#define coluna 60

struct matrizes{
	
	long int A[linha][coluna];
	long int B[linha][coluna];
	long int C[linha][coluna];

}typedef matrizes;

	//estrutura global
	matrizes mtz;
	
void num_aleatorios(long int A[linha][coluna], long int B[linha][coluna]){

		int i, j;

		srand(time(NULL));

		for(i=0; i<linha; i++){
			for(j=0; j<coluna; j++){
			
				A[i][j] = rand();
				B[i][j] = rand();

			}
		}
}

void printar(long int matriz[linha][coluna]){

		int i, j;
		
		for(i=0; i<linha; i++){
			for(j=0; j<coluna; j++){
			
				printf("%ld ", matriz[i][j]);
			}

			printf("\n");
		}
}

void *f1(void *f){

	int i, j;
		
		for(i=0; i< (coluna/2); i++){
			for(j=0; j< (linha/2); j++){
			
				mtz.C[i][j] = mtz.A[i][j] + mtz.B[i][j];
			}

		}

}

void *f2(void *f){

	int i, j;
		
		for(i=(coluna/2); i<coluna; i++){
			for(j=0; j< (linha/2); j++){
			
				mtz.C[i][j] = mtz.A[i][j] + mtz.B[i][j];
			}

		}

}

void *f3(void *f){

	int i, j;
		
		for(i=0; i< (coluna/2); i++){
			for(j=(linha/2); j<linha; j++){
			
				mtz.C[i][j] = mtz.A[i][j] + mtz.B[i][j];
			}

		}

}

void *f4(void *f){

	int i, j;
		
		for(i=(coluna/2); i<coluna; i++){
			for(j=(linha/2); j<linha; j++){
			
				mtz.C[i][j] = mtz.A[i][j] + mtz.B[i][j];
			}

		}

}

int main(int argc, char **argv){

	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3;
	pthread_t thread4;

	num_aleatorios(mtz.A, mtz.B);

  	//pthread_create(id_da_thread, Objeto_NULL, função, Argumento)
	pthread_create(&thread1, NULL, &f1, NULL);
	pthread_create(&thread2, NULL, &f2, NULL);
	pthread_create(&thread3, NULL, &f3, NULL);
	pthread_create(&thread4, NULL, &f4, NULL);
	
	//pthread_join(id_da_thread, retorno_da_thread)
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);
	pthread_join(thread4, NULL);

	printar(mtz.C);

	
	
	
return 0; 
}

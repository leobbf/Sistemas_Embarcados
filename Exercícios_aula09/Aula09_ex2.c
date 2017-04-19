#include <stdio.h>
#include <fcntl.h>	// Para a funcao open()
#include <unistd.h>	// Para a funcao close()
#include <stdlib.h>	// Para a função exit()
#include <string.h> // Para funções com string
#include <sys/types.h> //para função system()
#include <signal.h> //para sinais
#include <pthread.h> // para thread 
#include <time.h> //para função time(NULL)

#define linha 10
#define coluna 10

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
			
				A[i][j] = rand() % 10;
				B[i][j] = rand() % 10;

			}
		}
}

void printar(long int matriz[linha][coluna]){

		int i, j;

		printf("\n");

		for(i=0; i<linha; i++){
			for(j=0; j<coluna; j++){
			
				printf("%ld ", matriz[i][j]);
			}

			printf("\n");
		}
}

void *f1(){

	int i, j, t;
	long int aux = 0;
		
		for(i=0; i< (coluna/2); i++){
			for(j=0; j< (linha/2); j++){
			
				aux = (mtz.A[i][0] * mtz.B[0][j]) + aux;
			}

		}


}

int main(int argc, char **argv){

	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3;
	pthread_t thread4;

	num_aleatorios(mtz.A, mtz.B);

	pthread_create(&thread1, NULL, &f1, NULL);
	pthread_create(&thread2, NULL, &f2, NULL);
	pthread_create(&thread3, NULL, &f3, NULL);
	pthread_create(&thread4, NULL, &f4, NULL);	
	
	
return 0; 
}

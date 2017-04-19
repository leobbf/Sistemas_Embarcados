#include <stdio.h>
#include <fcntl.h>	// Para a funcao open()
#include <unistd.h>	// Para a funcao close()
#include <stdlib.h>	// Para a função exit()
#include <string.h> // Para funções com string
#include <sys/types.h> //para função system()
#include <signal.h> //para sinais
#include <pthread.h> // para thread 
#include <time.h> //para função time(NULL)


void num_aleatorios(long int A[60][60], long int B[60][60]){

		int i, j;

		srand(time(NULL));

		for(i=0; i<60; i++){
			for(j=0; j<60; j++){
			
				A[i][j] = rand();
				B[i][j] = rand();

			}
		}
}

void soma_A_B(long int A[60][60], long int B[60][60], long int C[60][60]){

		int i, j;
		
		for(i=0; i<60; i++){
			for(j=0; j<60; j++){
			
				C[i][j] = A[i][j] + B[i][j];
			}

		}
}

void printar(long int matriz[60][60]){

		int i, j;
		
		for(i=0; i<60; i++){
			for(j=0; j<60; j++){
			
				printf("%ld ", matriz[i][j]);
			}

			printf("\n");
		}
}

int main(int argc, char **argv){

	//C = A + B
	long int A[60][60];
	long int B[60][60];
	long int C[60][60];

	
	num_aleatorios(A, B);
	soma_A_B(A, B, C);
	printar(C);
	
	
return 0; 
}

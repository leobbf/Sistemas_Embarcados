#include <stdio.h>
#include <fcntl.h>	// Para a funcao open()
#include <unistd.h>	// Para a funcao close()
#include <stdlib.h>	// Para a função exit()
#include <string.h> // Para funções com string
#include <sys/types.h> //para função system()
#include <signal.h> //para sinais
#include <pthread.h> // para thread 


	int v_global = 0;

void *funcao_thread(){


		while(v_global <= 10){

			printf("%d\n", v_global);
			sleep(1);

		}	
}

int main(int argc, char **argv){

	pthread_t thread_id;
	int i;
	pthread_create(&thread_id, NULL, &funcao_thread, NULL);

	for(i=1; i<=11; i++){
		
		v_global++;
		sleep(1);

	} 


	pthread_join(thread_id, NULL);
	//printf("Programa principal terminou...\n");


return 0; 
}

#include <stdio.h>
#include <fcntl.h>	// Para a funcao open()
#include <unistd.h>	// Para a funcao close()
#include <stdlib.h>	// Para a função exit()
#include <string.h> // Para funções com string
#include <sys/types.h> //para função system()
#include <signal.h>


void trata_alarm(){
		
		system("ps");
		alarm(1);

}

void trata_final(){

		printf("\nProcesso terminado!\n");
		exit(0);
}


int main(int argc, char **argv){

	signal(SIGALRM, trata_alarm);
	signal(SIGINT, trata_final);

	printf("iniciando alarme de 1 segundo...\n");

	alarm(1);

	while(1);


return 0; 
}

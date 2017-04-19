#include <stdio.h>
#include <fcntl.h>	// Para a funcao open()
#include <unistd.h>	// Para a funcao close()
#include <stdlib.h>	// Para a função exit()
#include <string.h> // Para funções com string
#include <sys/types.h> //para função system()

int main(int argc, char **argv){

	int i;
	pid_t pid_filho[50] = fork();

	for(i=1; i<=argc; i++){

		if(pid_filho[i] == 0){
			
			printf("filho %d: %d\n",i , (int)getpid());
			system(argv[i]);

		}else{

			pid_filho[i+1] = fork();
			printf("pai: %d\n", (int)getpid());
		}
	}

return 0; 
}

#include <stdio.h>
#include <fcntl.h>	// Para a funcao open()
#include <unistd.h>	// Para a funcao close()
#include <stdlib.h>	// Para a função exit()
#include <string.h> // Para funções com string
#include <sys/types.h> //para função system()


int main(int argc, char **argv){

	pid_t pid_filho;
	int fp[2], bp=0, bf=0, i, j;

	pipe(fp);
	pid_filho = fork();

	//processo filho recebe valores (1 a 10) do processo pai via pipe e fd[0]

	if(pid_filho == 0){

		printf("filho começando a receber dados\n");

		for(i=0; i<10; i++){

			if(read(fp[0], &bf, sizeof(int)) < 0){

				printf("filho: erro ao ler do pipe\n");

			}else{
		
				printf("Filho leu: %d\n", bf);

			}

			sleep(1);
		}

		printf("filho terminou!\n");
	
	}

	//processo pai envia valores (1 a 10) para o processo filho via pipe e fd[1]

	else{
			
		printf("Pai començando a enviar dados\n");

		for(j=0; j<10; j++){

			bp = j+1;
			if(write(fp[1], &bp, sizeof(int)) < 0){

				printf("Pai: erro ao enviar para o pipe\n");

			}else{
				//printf("pai envia: %d\n", bp);
			}

			sleep(1);
		}

		sleep(1);		
		printf("pai terminou!\n");
	}

return 0; 
}

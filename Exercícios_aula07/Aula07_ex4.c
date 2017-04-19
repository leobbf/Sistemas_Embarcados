#include <stdio.h>
#include <fcntl.h>	// Para a funcao open()
#include <unistd.h>	// Para a funcao close()
#include <stdlib.h>	// Para a função exit()
#include <string.h> // Para funções com string
#include <sys/types.h> //para função system()
#include <signal.h>

	int vg_com = 0;

void comunicacao(){

	vg_com++;

}


int main(int argc, char **argv){


	pid_t processo;
	int fp[2];

	if(pipe(fp) < 0) printf("Erro na criação do pipe\n");
	
	if((processo = fork()) < 0) printf("Erro na criação do processo filho\n");

	signal(SIGALRM, comunicacao);


	//processo filho
	if(processo == 0){

		char bf[100]; //buffer do filho

		printf("insira seu nome de usuário: ");
		scanf("%s", bf);

		printf("filho leu o nome de usuário. enviando para o pai...\n");

		if(write(fp[1], bf, sizeof(bf)) < 0){
			printf("erro na escrita no pipe\n");
		}else{
			
			alarm(1);
		}

		sleep(1);
		exit(0);

	}

	//processo pai
	else{

		char bp[100];//buffer do pai;

		//tem que receber um sinal do filho 
		while(vg_com == 0);

		printf("pai vai ler o nome de usuário.\n");		

		if(read(fp[0], bp, sizeof(bp)) < 0){
			printf("erro na leitura do pipe\n");
		}else{
			
			printf("nome de usuário: %s\n", bp);
		}

		exit(0);

	}

return 0; 
}

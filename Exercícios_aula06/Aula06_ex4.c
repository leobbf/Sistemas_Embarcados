#include <stdio.h>
#include <fcntl.h>	// Para a funcao open()
#include <unistd.h>	// Para a funcao close()
#include <stdlib.h>	// Para a função exit()
#include <string.h> // Para funções com string
#include <sys/types.h> //para função system()


int v_global = 0; // Variavel global para este exemplo

void Incrementa_Variavel_Global(pid_t id_atual){

		v_global++;
		printf("ID do processo que executou esta funcao = %d\n", id_atual);
		printf("v_global = %d\n", v_global);
}

int main(int argc, char **argv){

	pid_t pid_filho_1 = fork();
	pid_t pid_filho_2;
	pid_t pid_filho_3;

	if(pid_filho_1 == 0){
		//printf("filho 1: %d\n", (int)getpid());
		Incrementa_Variavel_Global(getpid());
			
	}else{

		pid_filho_2 = fork();

		if(pid_filho_2 == 0){
			//printf("filho 2: %d\n", (int)getpid());
			Incrementa_Variavel_Global(getpid());
			
		}else{

			pid_filho_3 = fork();
		
			if(pid_filho_3 == 0){
				//printf("filho 3: %d\n", (int)getpid());
				Incrementa_Variavel_Global(getpid());
				
			}else{
			
				printf("pai: %d\n", (int)getpid());

			}
		}
	}


return 0; 
}

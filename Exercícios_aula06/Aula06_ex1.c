#include <stdio.h>
#include <fcntl.h>	// Para a funcao open()
#include <unistd.h>	// Para a funcao close()
#include <stdlib.h>	// Para a função exit()
#include <string.h>
#include <sys/types.h>

int main(int argc, char **argv){

	pid_t pid_filho_1 = fork();
	pid_t pid_filho_2;
	pid_t pid_filho_3;

	//printf("pai: %d\n", (int)getpid());

	if(pid_filho_1 == 0){
		printf("filho 1: %d\n", (int)getpid());
			
	}else{

		pid_filho_2 = fork();

		if(pid_filho_2 == 0){
			printf("filho 2: %d\n", (int)getpid());
			
		}else{

			pid_filho_3 = fork();
		
			if(pid_filho_3 == 0){
				printf("filho 3: %d\n", (int)getpid());
				
			}else{
			
				printf("pai: %d\n", (int)getpid());

			}
		}
	}


return 0; 
}

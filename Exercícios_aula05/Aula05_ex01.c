#include <stdio.h>	// Para a funcao printf()
#include <fcntl.h>	// Para a funcao open()
#include <unistd.h>	// Para a funcao close()
#include <stdlib.h>	// Para a função exit()

int main(int argc, char **argv){

	int fp; 
	fp = open("ola_mundo.txt", O_CREAT | O_RDWR);

	if(fp==-1){

		printf ("Erro na abertura do arquivo.\n");
		exit (1);
	}


		write(fp, "ola Mundo!\n", sizeof(char)*12);

	close(fp);
return 0;
}

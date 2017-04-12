#include <stdio.h>
#include <fcntl.h>	// Para a funcao open()
#include <unistd.h>	// Para a funcao close()
#include <stdlib.h>	// Para a função exit()
#include <string.h>
#include <sys/types.h>

int main(int argc, char **argv){

	char *argumento;
	int i;

	for(i=1; i<=argc; i++){

		argumento = argv[i];

		system(argumento);

	}


return 0; 
}

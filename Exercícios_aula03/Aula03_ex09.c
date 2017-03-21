#include <stdio.h>
#include "num_caracs.h"

int main(int argc, char **argv){

	int i;

	for(i=0; i < argc; i++){
	
		printf("Argumento: %s / Numero de caracteres: %d\n", argv[i], num_caracs(argv[i]));
	
		
	}

return 0;
}

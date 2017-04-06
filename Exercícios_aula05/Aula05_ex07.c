#include <stdio.h>
#include <fcntl.h>	// Para a funcao open()
#include <unistd.h>	// Para a funcao close()
#include <stdlib.h>	// Para a função exit()
#include <string.h>
#include "bib_arqs.h"

int main(int argc, char **argv){

	int fp, quantidade;
	char nome_aux[100], palavra_chave[100];

	sprintf(palavra_chave, "%s", argv[1]);
	sprintf(nome_aux, "%s", argv[2]);

		//grep_falso(nome_aux, palavra_chave); 

	quantidade = grep_falso(nome_aux, palavra_chave); 

	printf("'%s' ocorre %d no arquivo '%s.txt'\n", palavra_chave, quantidade, nome_aux);

return 0; 
}

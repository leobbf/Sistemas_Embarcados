#include <stdio.h>
#include "bib_arqs.h"

int main(int argc, char **argv){

	char palavra_chave[100];
	char nome_arquivo[100];
	int quantidade;

	sprintf(palavra_chave, "%s", argv[1]);
	sprintf(nome_arquivo, "%s", argv[2]);

	quantidade = grep_falso(nome_arquivo, palavra_chave);
	
	printf("'%s' ocorre %d no arquivo '%s'\n",palavra_chave, quantidade, nome_arquivo); 

return 0; 
}

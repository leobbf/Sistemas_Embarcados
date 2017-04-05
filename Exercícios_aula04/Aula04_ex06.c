#include <stdio.h>
#include "bib_arqs.h"

int main(int argc, char **argv){

	char nome_arquivo[100];
	char conteudo[100];

	sprintf(nome_arquivo, "%s", argv[1]);

	le_arq_texto(nome_arquivo, conteudo);
	
	printf("%s", conteudo); 

return 0; 
}

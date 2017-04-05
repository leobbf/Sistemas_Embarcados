#include <stdio.h>
#include "bib_arqs.h"

int main(){

	char nome_arquivo[100];
	char conteudo[100];

	printf("Nome do arquivo: ");
	scanf("%s", nome_arquivo);

	le_arq_texto(nome_arquivo, conteudo);
	
	printf("%s", conteudo); 

return 0; 
}

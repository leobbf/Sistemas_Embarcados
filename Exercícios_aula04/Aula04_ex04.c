#include <stdio.h>
#include "bib_arqs.h"

int main(){

	char nome_arquivo[100];

	printf("Nome do arquivo: ");
	scanf("%s", nome_arquivo);

	printf("%d\n", tam_arq_texto(nome_arquivo)); 

return 0; 
}

#include <stdio.h>
#include <fcntl.h>	// Para a funcao open()
#include <unistd.h>	// Para a funcao close()
#include <stdlib.h>	// Para a função exit()
#include "bib_arqs.h"

int main(){

	char nome_arquivo[100], conteudo[100];

	printf("Nome do arquivo: ");
	scanf("%s", nome_arquivo);

	le_arq_texto(nome_arquivo, conteudo); 

return 0; 
}

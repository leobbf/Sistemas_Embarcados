#include <stdio.h>
#include "bib_arqs.h"

int tam_arq_texto(char *nome_arquivo){

	FILE *fp = fopen(nome_arquivo, "r");
	int tamanho;	

	fseek(fp, 0, SEEK_END);
	tamanho = ftell(fp);

	fclose(fp);


return tamanho;
}

void le_arq_texto(char *nome_arquivo, char *conteudo){

	FILE *fp = fopen(nome_arquivo, "r");
	int i, tamanho;

	fseek(fp, 0, SEEK_END);
	tamanho = ftell(fp);
	rewind(fp);

	for(i=0; i < tamanho; i++){

		conteudo[i] = getc(fp);
	}

	fclose(fp);
}


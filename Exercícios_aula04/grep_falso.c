#include <stdio.h>
#include <string.h>
#include "bib_arqs.h"

int grep_falso(char *nome_arquivo, char *palavra_chave){

	FILE *fp = fopen(nome_arquivo, "r");
	int i, j, tamanho_arquivo, tamanho_palavra, quantidade=0;
	char conteudo[100], palavra[100];

// lê o arquivo e coloca em conteudo e lê a palavra_chave e coloca em palavra
	le_arq_texto(nome_arquivo, conteudo);
	sprintf(palavra, "%s", palavra_chave);

//calcula o tamanho do arquivo e da palavra_chave
	
	tamanho_arquivo = tam_arq_texto(nome_arquivo);
	tamanho_palavra = strlen(palavra);

//compara a palavra_chave com o arquivo


	while(i < tamanho_arquivo){

		if(palavra[j] == conteudo[i]){
			j++;
		}else{
			j = 0;
		}

		if(j == tamanho_palavra){
			quantidade++;
			j = 0;
		}
		i++;
	}

	fclose(fp);

	return quantidade;


}

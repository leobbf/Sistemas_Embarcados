#include <stdio.h>
#include <fcntl.h>	// Para a funcao open()
#include <unistd.h>	// Para a funcao close()
#include <stdlib.h>	// Para a função exit()
#include <string.h>
#include "bib_arqs.h"

int tam_arq_texto(char *nome_arquivo){

	int fp; 
	int i=0;
	char c;

	fp = open(nome_arquivo, O_RDONLY);

	if(fp==-1){

		printf ("Erro na abertura do arquivo.\n");
		exit (1);
	}	


		while(read(fp, &c, sizeof(char)) != '\0'){
		
			if(c != '\0') i++;
		}


	close(fp);


return i-1;
}

void le_arq_texto(char *nome_arquivo, char *conteudo){

	int fp, i=0;
	char c, cont_aux[100];

	fp = open(nome_arquivo, O_RDONLY);

	if(fp==-1){

		printf ("Erro na abertura do arquivo.\n");
		exit (1);
	}

	for(i=0; read(fp, &c, sizeof(char)); i++){
	
		if(c != '\0') cont_aux[i] = c;

	}	
	
		printf("%s\n", cont_aux);


	close(fp);
}

int grep_falso(char *nome_arquivo, char *palavra_chave){


	char nome_aux[100], chave_aux[100], cont_aux[100], c;
	int i, j, quantidade=0, fp;
	int tamanho_arquivo, tamanho_chave;

	sprintf(nome_aux, "%s", nome_arquivo);
	sprintf(chave_aux, "%s", palavra_chave);

	fp = open(nome_aux, O_RDONLY);

	if(fp==-1){

		printf ("Erro na abertura do arquivo.\n");
		exit (1);
	}

	for(i=0; read(fp, &c, sizeof(char)); i++){
	
		if(c != '\0') cont_aux[i] = c;

	}

	tamanho_arquivo = strlen(cont_aux);
	tamanho_chave = strlen(chave_aux);
	i=0;
	j=0;

/*	printf("tamanho arquivo: %d\n", tamanho_arquivo);*/
/*	printf("tamanho chave: %d\n", tamanho_chave);*/

	for(i=0; i < tamanho_arquivo; i++){

/*		printf("%c == %c\n", chave_aux[j], cont_aux[i]);*/
		
		if(chave_aux[j] == cont_aux[i]){
			j++;
	
		}else j = 0;

		if(j == tamanho_chave){
			quantidade++;
			j = 0;
		}

/*		printf("i: %d\n", i);*/
/*		printf("j: %d\n", j);*/

	}
		

	close(fp);

	return quantidade;
}


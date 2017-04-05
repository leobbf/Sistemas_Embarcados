#include <stdio.h>

int main(){

	char nome[100], nome_aux[100];
	int idade;
	FILE *fp;

	printf("Digite seu nome: ");
	scanf("%s", nome);
	printf("Digite sua idade: ");
	scanf("%d", &idade);

	sprintf(nome_aux, "%s.txt", nome);

	fp = fopen(nome_aux, "w");

	fprintf(fp, "Nome: %s \nIdade: %d \n", nome, idade);
	
	fclose(fp);

return 0;
}

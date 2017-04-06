#include <stdio.h>	// Para a funcao printf()
#include <fcntl.h>	// Para a funcao open()
#include <unistd.h>	// Para a funcao close()
#include <stdlib.h>	// Para a função exit()

int main(int argc, char **argv){

	int fp, i;
	char nome[100], nome_aux[100], idade[3];

	printf("Digite seu nome: ");
	scanf("%s", nome);
	printf("Digite sua idade: ");
	scanf("%s", idade);

	sprintf(nome_aux, "%s.txt", nome);

	fp = open(nome_aux, O_CREAT | O_RDWR);
	
	if(fp==-1){

		printf ("Erro na abertura do arquivo.\n");
		exit (1);
	}

		write(fp, "Nome: ", 6);

		for(i=0; nome[i]; i++)
			write(fp, &nome[i], sizeof(char));

		write(fp, "\nIdade: ", 8);	
		
		for(i=0; idade[i]; i++)
			write(fp, &idade[i], sizeof(char));	

		write(fp, "\n", 1);

	close(fp);

return 0;
}

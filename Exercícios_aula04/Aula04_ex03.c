#include <stdio.h>

int main(int argc, char **argv){
 
	char nome_aux[100];
	char idade;
	FILE *fp;

	sprintf(nome_aux, "%s.txt", argv[1]);

	fp = fopen(nome_aux, "w");

	fprintf(fp, "Nome: %s \nIdade: %s anos \n", argv[1], argv[2]);
	
	fclose(fp);

return 0;
}

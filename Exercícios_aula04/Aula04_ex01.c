#include <stdio.h>

int main(){

	FILE *fp = fopen("ola_mundo.txt", "w");
	fprintf(fp, "Ola mundo!");
	fclose(fp);

return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <signal.h>
#include <time.h>

#define gpio_past "/sys/class/gpio"
#define valid_io 2,3,4,5,6,7,8,9,10,11,12,13,16,17,18,19,20,21,22,23,24,25,26

int main(int argc, char **argv){

	int fd;
	
	puts("\n Blink Led on GPIO4 \n");
	
	//abrindo o arquivo export para definir qual pino será usado
	if((fd = open("/sys/class/gpio/export", O_RDWR)) < 0){
		puts("Erro na abertura do arquivo Export\n");
		exit(0);
	}
	
	//definindo pino 4 para uso
	if(write(fd, "4", sizeof(char)) < 0){
		puts("falha na escrita do arquivo export\n");
		exit(0);
	}
	
	close(fd);
	
	//abrindo o arquivo direction para definir I/O
	if((fd = open("/sys/class/gpio/gpio4/direction", O_RDWR)) < 0){
		puts("Erro na abertura do arquivo direction\n");
		exit(0);
	}
	
	//definindo pino 4 como OUT
	if(write(fd, "out", sizeof(char)*3) < 0){
		puts("falha na escrita do arquivo direction\n");
		exit(0);
	}
	
	close(fd);
	
	//abrindo o arquivo value do pino 4 para definir se HIGH ou LOW
	if((fd = open("/sys/class/gpio/gpio4/value", O_RDWR)) < 0){
		puts("Erro na abertura do arquivo value\n");
		exit(0);
	}
	
	//definindo HIGH para pino OUT 4
	if(write(fd, "1", sizeof(char)) < 0){
		puts("falha na escrita do arquivo value\n");
		exit(0);
	}
	
	//espera 5 segundos
	sleep(5);
	
	//definindo LOW para pino OUT 4
	if(write(fd, "0", sizeof(char)) < 0){
		puts("falha na escrita do arquivo value\n");
		exit(0);
	}
	
	close(fd);
	
	
	//abrindo o arquivo unexport para fechar o pino usado
	if((fd = open("/sys/class/gpio/unexport", O_RDWR)) < 0){
		puts("Erro na abertura do arquivo unexport\n");
		exit(0);
	}
	
	//fechando o pino 4
	if(write(fd, "4", sizeof(char)) < 0){
		puts("falha na escrita do arquivo export\n");
		exit(0);
	}
	
	close(fd);
	
return 0;
}
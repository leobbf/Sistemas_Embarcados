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

int fd;

void tratamento_sinal(){

	puts("\n apertou Ctrl+c ou deu algum erro...\n Parando o programa\n");
	
	close(fd);
	
	//abrindo o arquivo unexport para fechar o pino usado
	if((fd = open("/sys/class/gpio/unexport", O_RDWR)) < 0){
		puts("Erro na abertura do arquivo unexport\n");
		exit(0);
	}
	
	//fechando o pino 4
	if(write(fd, "4", sizeof(char)) < 0){
		puts("falha na escrita do arquivo unexport\n");
		exit(0);
	}
	
	
	//fechando o pino 3
	if(write(fd, "3", sizeof(char)) < 0){
		puts("falha na escrita do arquivo unexport\n");
		exit(0);
	}
	
	close(fd);
	
	exit(0);
}

int main(int argc, char **argv){
	
	int fp[2];
	pid_t processos;
	
	if(pipe(fp) < 0){ 
		puts("Erro na criação do pipe");
		exit(0);
	}
	
	if((processos = fork()) < 0){
		puts("Erro na criação dos processos");
		exit(0);
	}
	
	//ativando sinal Ctrl+C
	signal(SIGINT, tratamento_sinal);
	
	puts("\n Blink Led on GPIO4 \n");
	
	//processo filho
	if(processos == 0){

		char bf = 1;

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
			puts("Execute esse programa como super usuario!! se não vai dar errado sempre \n");
			tratamento_sinal();
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
		
		while(1){
	
		if(read(fp[0], &bf, sizeof(bf)) < 0){
			puts("Erro na leitura do pipe");
		}

	printf("BUFFER FILHO = %c\n",bf);

		//definindo HIGH para pino OUT 4
		if(write(fd, "1", sizeof(char)) < 0){
			puts("falha na escrita do arquivo value\n");
			exit(0);
		}
		
		//espera 0.5/bf segundos
		usleep(500000.0/(int) bf);
		
		//definindo LOW para pino OUT 4
		if(write(fd, "0", sizeof(char)) < 0){
			puts("falha na escrita do arquivo value\n");
			exit(0);
		}
		
		//espera 0.5/bf segundos
		usleep(500000.0/(int) bf);
	
		}

	}
	
	//processo pai
	else{
	
		int bp=1; char btn;
	
		//abrindo o arquivo export para definir qual pino será usado
		if((fd = open("/sys/class/gpio/export", O_RDWR)) < 0){
			puts("Erro na abertura do arquivo Export\n");
			exit(0);
		}
		
		//definindo pino 3 para uso
		if(write(fd, "3", sizeof(char)) < 0){
			puts("falha na escrita do arquivo export\n");
			exit(0);
		}
		
		close(fd);
		
		//abrindo o arquivo direction para definir I/O
		if((fd = open("/sys/class/gpio/gpio3/direction", O_RDWR)) < 0){
			puts("Erro na abertura do arquivo direction\n");
			puts("Execute esse programa como super usuario!! se não vai dar errado sempre \n");
			tratamento_sinal();
		}
		
		//definindo pino 3 como IN
		if(write(fd, "in", sizeof(char)*2) < 0){
			puts("falha na escrita do arquivo direction\n");
			exit(0);
		}

		close(fd);
		
		//abrindo o arquivo value do pino 3
		if((fd = open("/sys/class/gpio/gpio3/value", O_RDWR)) < 0){
			puts("Erro na abertura do arquivo value\n");
			exit(0);
		}
		
		while(1){

			lseek(fd, 0, SEEK_SET);
			//leitura do value
			if(read(fd, &btn, 1) < 0){
				puts("falha na leitura do arquivo ");
			}

printf("BTN = %c\n",btn);

			if(btn == '1'){
				bp = bp*2;
				printf("BP = %d\n",bp);
				if(write(fp[1], &bp, sizeof(bp)) < 0){

					puts("Erro na escrita do pipe");
				}
				if(bp == 128) bp=1;


			}

		}

	}
return 0;
}

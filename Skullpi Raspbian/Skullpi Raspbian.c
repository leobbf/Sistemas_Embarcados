#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <signal.h>
#include <time.h>

int fd;

void encerrar(){

	puts("\nctrl+c... Fechando programa...\n");
	close(fd);
	exit(0);
}

void veri_skullpi(){

//verificando a existencia da pasta Skullpi

	char bf_skullpi = '0';
	char *file = "/tmp/ver_skullpi.txt";
	
	do{
	
		system("./veri_skullpi.sh");
		usleep(500000);
		
		printf("Status Open skullpi = %d\n", (fd = open(file, O_RDONLY | O_CREAT)));
		
		lseek(fd, 0, SEEK_SET);
		
		printf("Status Read skullpi = %d\n", (read(fd, &bf_skullpi, sizeof(char))));
			
		close(fd);
		
		if(bf_skullpi == '0'){
			system("./creat.sh");
		
		}
	
	}while(bf_skullpi == '0');


}

void veri_cadastrados(){

//verificando a existencia do arquivo cadastrados

	char bf_cadastrados = '0';
	char *file = "/tmp/ver_cadastrados.txt";
	
	do{
	
		system("./veri_cadastrados.sh");
		usleep(500000);
		
		printf("Status Open ver_cadastrados = %d\n", (fd = open(file, O_RDONLY | O_CREAT)));
		
		lseek(fd, 0, SEEK_SET);
		
		printf("Status Read ver_cadastrados  = %d\n", (read(fd, &bf_cadastrados, sizeof(char))));
			
		close(fd);
		
		if(bf_cadastrados == '0'){
			system("cd /home/pi && echo \"Cadastrados na Skullpi: \" > cadastrados.txt ");
			system("chmod 777 /home/pi/cadastrados.txt");
		
		}
	
	}while(bf_cadastrados == '0');


}

char veri_pac(){

//verificando a existencia do compactado pac.tar

	char bf_pac = '0';
	char *file = "/tmp/ver_pac.txt";
	
		system("./veri_pac.sh");
		usleep(500000);
		
		printf("Status Open pac = %d\n", (fd = open(file, O_RDONLY | O_CREAT)));
		
		lseek(fd, 0, SEEK_SET);
		
		printf("Status Read pac = %d\n", (read(fd, &bf_pac, sizeof(char))));
			
		close(fd);
	
		return bf_pac;

}

char veri_login(){

//verificando se existe um novo login

	char bf_login = '0';
	char *file = "/tmp/ver_login1.txt";
	
		system("./veri_login.sh");
		
		printf("Status Open ver_login = %d\n", (fd = open(file, O_RDONLY)));
		
		lseek(fd, 0, SEEK_SET);
		
		printf("Status Read ver_login = %d\n", (read(fd, &bf_login, sizeof(char))));
			
		close(fd);
	
		return bf_login;

}

void cad_login(){

	char bf_cad[100];
	char buffer[100];
	char *file1 = "/tmp/login.txt";
	char *file2 = "/home/pi/cadastrados.txt";
	
	//lendo novo login
	printf("Status open cad_login = %d", (fd = open(file1, O_RDONLY)));
	printf("Status read cad_login = %d", (read(fd, &bf_cad, sizeof(bf_cad))));
	close(fd);
	system("cd /tmp && rm login.txt");
	
	//adicionando em cadastrados
	sprintf(buffer,"%s", bf_cad);
	printf("Status open cadastrados = %d", (fd = open(file2, O_APPEND | O_WRONLY)));
	system("cd /home/pi && chmod 777 cadastrados.txt");
	printf("Status write cadastrados = %d", (write(fd, &buffer, strlen(buffer))));
	close(fd);

}

int main(){

	char buffer;
	pid_t pid;
	
	signal(SIGINT, encerrar);
	
	printf("Status fork = %d", (pid = fork()));
	
//processo Pai, realiza os procedimentos de upload e download de arquivos
	if(pid != 0){
	
		veri_skullpi();
		system("./compak.sh");
	
		while(1){
		
			sleep(1);
			
			if(veri_pac() == '1'){
				system("./descomp.sh");
				system("./compak.sh");
				
			}
		
		}
	}
	
//processo filho, realiza os procedimentos de login
	else{
	
		veri_cadastrados();
	
		while(1){
			
			sleep(1);
			
			if(veri_login() == '1'){ 
				cad_login();
			}
			
		}
	}
	

return 0;
}

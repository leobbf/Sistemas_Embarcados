//Skullbian v 2.0


/*
	Essa é a versão 2.0 do software que controla o sistema de gerenciamento de arquivo em nuvem, Skullpi.

	Existem 4 "capítulos" nesse código que dividem a rotina de processos do Skullpi e os três grupos de funções, os quais operam os procedimentos de: preparação de arquivos iniciais (Diretório Skullpi, Lista de cadastrados e Lista de em saque), gerenciamento do sistema (cadastro de login e saque, manutenção de upload e preparação do download), bem como subrotinas para manipulação de arquivos (compactação e transporte).


	Esse software atua como servidor e banco de dados e opera de forma autônoma com a recepção e preparação de arquivos recebendo e armazenando dados via conexão Wifi pela rede Skullpi roteada atraves do raspberry pi 3.
	
																																	*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <signal.h>
#include <time.h>

void compactar_arquivos();
void descompactar_arquivos();

int fd;
FILE *fd2;
int qntd_cad = 0;


void encerrar(){

	puts("\nctrl+c... Fechando programa...\n");
	close(fd);
	exit(0);
}

//------------------------------------------------- Funções Alfa: Preparação -----------------------------------------------------------//

/* 

	As funções a baixo asseguram que todos os diretórios e arquivos para criação e manutenção do sistema Skullpi sejam criados

		veri_skullpi, veri_cadastrados, veri_emsaque.


*/

void veri_skullpi(){

//verificando a existencia da pasta Skullpi, se não existir cria-a.

	char bf_skullpi = '0';
	char buffer[100] = " "; 
	char *file = "/tmp/ver_skullpi.txt";
	int i;
	
		system("./veri_skullpi.sh");
		printf("Status Open skullpi = %d\n", (fd = open(file, O_RDONLY | O_CREAT)));
		lseek(fd, 0, SEEK_SET);
		printf("Status Read skullpi = %d\n", (read(fd, &bf_skullpi, sizeof(char))));
		close(fd);
		if(bf_skullpi == '0'){ 
			system("cd /home/pi && mkdir Skullpi");
			for(i=0; i<10; i++){
				sprintf(buffer,"cd /home/pi/Skullpi && mkdir usr%d", i);
				system(buffer);
			}
			system("chmod 777 -R /home/pi/Skullpi");
		}
		
}

void veri_cadastrados(){

//verificando a existencia do arquivo cadastrados, se não existir cria-o.

	char bf_cadastrados = '0';
	char *file = "/tmp/ver_cadastrados.txt";
	
		system("./veri_cadastrados.sh");
		printf("Status Open ver_cadastrados = %d\n", (fd = open(file, O_RDONLY | O_CREAT)));
		lseek(fd, 0, SEEK_SET);
		printf("Status Read ver_cadastrados  = %d\n", (read(fd, &bf_cadastrados, sizeof(char))));	
		close(fd);
		if(bf_cadastrados == '0'){
			system("cd /home/pi && echo \"Cadastrados no Skullpi: \" > cadastrados.txt ");
			system("chmod 777 /home/pi/cadastrados.txt");
		
		}
	

}

/*void veri_emsaque(){

//verificando a existencia do arquivo emsaque.txt, se não existir cria-o.

	char bf_emsaque = '0';
	char *file = "/tmp/ver_emsaque.txt";
	
		system("./veri_emsaque.sh");
		printf("Status Open ver_emsaque = %d\n", (fd = open(file, O_RDONLY | O_CREAT)));
		lseek(fd, 0, SEEK_SET);
		printf("Status Read ver_emsaque  = %d\n", (read(fd, &bf_emsaque, sizeof(char))));	
		close(fd);
		if(bf_emsaque == '0'){

			system("cd /home/pi && echo \"em Saque no Skullpi: \" > emsaque.txt ");
			system("chmod 777 /home/pi/emsaque.txt");
		
		}


}*/

//------------------------------------ Funções Beta: Gerenciamento -----------------------------------------------//


/* 

	As funções a baixo coordenam todo o sistema, cadastro, saque, e atualização de diretórios.

	cadastrar, autoriza_saque, funcao_usr0~9 e interface gráfica.


*/

void cadastrar(){
	
	/*São 10 diretórios disponíveis 
	(0 a 9) dentro do Skullpi, essa função 
	atribui um nº de diretório, um login 
	e uma senha a um diretório disponível, 
	armazenando essas informações em um 
	arquivo chamado cadastrados.txt*/
	 
	char bf_cad[100] = " ";
	char buffer[100] = " ";
	char leitura[100];
	int i;
	
	
	//Lê o novo pedido (cad.txt) de cadastro e adiciona à cadastrados.txt
		
		printf("Status open cad.txt = %d\n", (fd = open("/tmp/cad.txt", O_RDONLY)));
		lseek(fd, 0, SEEK_SET);
		printf("Status read cad.txt = %d\n", (read(fd, &bf_cad, sizeof(bf_cad))));
		close(fd);
		system("rm /tmp/cad.txt");
		
		printf("leitura do cad.txt = %s\n", bf_cad);
		
		fd2 = fopen("/home/pi/cadastrados.txt", "r");
		fseek(fd2, 0, SEEK_SET);
			
			do{
			
			  	fgets(leitura, 100, fd2);
				qntd_cad++;
			
			
			}while(!feof(fd2));
			fclose(fd2);
			
			qntd_cad -= 2;
			printf("qntd_cad = %d\n", qntd_cad);
			
		if(qntd_cad == 10){
			
			puts("Não há diretórios disponíveis para cadastro!");
			
		}else{
			
		sprintf(buffer,"%d %s\n",qntd_cad ,bf_cad);
		printf("escrita no cadastrados.txt = %s\n", buffer);
		printf("Status open cadastrados = %d\n", (fd = open("/home/pi/cadastrados.txt", O_APPEND | O_WRONLY)));
		printf("Status write cadastrados = %d\n", (write(fd, &buffer, strlen(buffer))));
		close(fd);
			
		}
					
}

void autoriza_saque(){

/*
		Ao autorizar o modo saque, o diretório passa a ser 
	"aberto" para download, ou seja, qualquer pessoa mesmo 
	sem cadastro poderia baixar as pastas que estejam em 
	modo saque.

*/

	char buffer[100] = " ";
	
	fd = open("/tmp/saque.txt", O_RDONLY);
	lseek(fd, 0, SEEK_SET);
	read(fd, &buffer, sizeof(buffer));
	close(fd);
	
	fd = open("/home/pi/emsaque.txt", O_APPEND | O_WRONLY);
	write(fd, &buffer, strlen(buffer));
	close(fd);
}

/*void interface(){*/

/*	char buffer[100] = " ";*/
/*	char nome_pasta[100] = " ";*/
/*	char usr;*/


/*	fd = open("/home/pi/emsaque.txt", O_RDONLY);*/
/*	lseek(fd, 0, SEEK_SET);*/
/*	read(fd, &usr);*/
/* 	*/

/*	system("dialog --title \"Saque Disponível:\" --msgbox \"  \" ")*/



/*}*/

/*

	As funções funcao_usr0~9 fazem o controle independente de cada um dos diretório presentes no Skullpi



*/

void funcao_usr0(){

	descompactar_arquivos(0);
	compactar_arquivos(0);
	system("rm /tmp/sinal_usr0.txt");

}
void funcao_usr1(){
	
	descompactar_arquivos(1);
	compactar_arquivos(1);
	system("rm /tmp/sinal_usr1.txt");

}
void funcao_usr2(){

	descompactar_arquivos(2);
	compactar_arquivos(2);
	system("rm /tmp/sinal_usr2.txt");

}
void funcao_usr3(){
	
	descompactar_arquivos(3);
	compactar_arquivos(3);
	system("rm /tmp/sinal_usr3.txt");

}
void funcao_usr4(){

	descompactar_arquivos(4);
	compactar_arquivos(4);
	system("rm /tmp/sinal_usr4.txt");

}
void funcao_usr5(){

	descompactar_arquivos(5);
	compactar_arquivos(5);
	system("rm /tmp/sinal_usr5.txt");

}
void funcao_usr6(){

	descompactar_arquivos(6);
	compactar_arquivos(6);
	system("rm /tmp/sinal_usr6.txt");

}
void funcao_usr7(){

	descompactar_arquivos(7);
	compactar_arquivos(7);
	system("rm /tmp/sinal_usr7.txt");

}
void funcao_usr8(){

	descompactar_arquivos(8);
	compactar_arquivos(8);
	system("rm /tmp/sinal_usr8.txt");

}
void funcao_usr9(){
	
	descompactar_arquivos(9);
	compactar_arquivos(9);
	system("rm /tmp/sinal_usr9.txt");

}

//------------------------------------ Funções Gama: tratamento de arquivos ----------------------------------------//


/*

		Essas subrotinas foram criadas para ajudar com a compactação e transporte de arquivos


*/

// 0 < usr < 9 --> PAK ou PAC (Download, Upload)
// 011 < usr < 911 --> PAS (Saque) 


void compactar_arquivos(int usr){

/* 
	essa função lida com os pacotes de saída para saque e download (PAK)
		

*/


	char buffer[100] = " ";

	
	
		sprintf(buffer,"cd /home/pi/Skullpi && tar -cf pak%d.tar usr%d", usr, usr);
		system(buffer);
		sprintf(buffer,"mv /home/pi/Skullpi/pak%d.tar /tmp", usr);
		system(buffer);


}

void descompactar_arquivos(int usr){

/* 
	essa função lida com os pacotes de entrada vindas do upload (PAC).
		

*/

	char buffer[100] = " ";
	
	sprintf(buffer,"mv /tmp/pac%d.tar /home/pi/Skullpi", usr);
	system(buffer);
	sprintf(buffer,"cd /home/pi/Skullpi && tar -xvf pac%d.tar", usr);
	system(buffer);
	sprintf(buffer,"rm /home/pi/Skullpi/pac%d.tar", usr);
	system(buffer);
	system("chmod 777 -R /home/pi/Skullpi");

}

//------------------------------------ Rotina principal de processos ------------------------------------------------//

/*
			Existem 12 processos filhos sendo monitorados pelo processo pai, os 10 primeiros (0 ao 9) realizam procedimentos de compactação de arquivos para os 10 diretórios presentes no Skullpi, respectivamente. O decimo primeiro filho(pid[10]) realiza procedimento de cadastro e o decimo segundo (pid[11]) autoriza o saque. 
			O pai verifica a entrega de pacode de dados (pac), vindas por upload, solicitadas pelos usuários sinalizando aos filhos qual o diretório deve ser atualizado. Gerando os pacotes de dados (pak) para download e saque sempre que um novo upload e rearranjado.
			O pai tbm verifica pedido de cadastramento e ensaque (situação onde usuário permite que seu diretório entrem em modo saque).
			
																																		*/

int main(){

	signal(SIGINT, encerrar);
	
	pid_t pid[13];
	char buffer[100];
	int i=0;
	
	veri_skullpi();
	veri_cadastrados();
	veri_emsaque();

	for(i=0; i<10; i++) compactar_arquivos(i);
	
	pid[0] = fork();
	
	//filho 0
	if(pid[0] == 0){ 

		signal(SIGUSR1, funcao_usr0);
		while(1) sleep(1);
	}
		
	else{
	pid[1] = fork();
	
	//filho 1
	if(pid[1] == 0){ 
	
		signal(SIGUSR1, funcao_usr1);
		while(1) sleep(1);
	}
		
	else{
	pid[2] = fork();
	
	//filho 2
	if(pid[2] == 0){ 
	
		signal(SIGUSR1, funcao_usr2);
		while(1) sleep(1);
	}
		
	else{
	pid[3] = fork();
				
	//filho 3
	if(pid[3] == 0){ 
		
		signal(SIGUSR1, funcao_usr3);
		while(1) sleep(1);
	}
				
	else{
	pid[4] = fork();
					
	//filho 4
	if(pid[4] == 0){ 
	
		signal(SIGUSR1, funcao_usr4);
		while(1) sleep(1);
	}
					
	else{
	pid[5] = fork();
						
	//filho 5					
	if(pid[5] == 0){ 
	
		signal(SIGUSR1, funcao_usr5);
		while(1) sleep(1);
	}	
						
	else{
	pid[6] = fork();
							
	//filho 6					
	if(pid[6] == 0){ 
	
		signal(SIGUSR1, funcao_usr6);
		while(1) sleep(1);
	}	
							
	else{
	pid[7] = fork();
								
	//filho 7						
	if(pid[7] == 0){ 
		
		signal(SIGUSR1, funcao_usr7);
		while(1) sleep(1);	
	}		
						
	else{
	pid[8] = fork();
	
	//filho 8
	if(pid[8] == 0){ 
	
		signal(SIGUSR1, funcao_usr8);
		while(1) sleep(1);
	}
									
	else{
	pid[9] = fork();
										
	//filho 9									
	if(pid[9] == 0){ 
	
		signal(SIGUSR1, funcao_usr9);
		while(1) sleep(1);
		
	}
	
									
	else{
	pid[10] = fork();
	
	//filho 10 (cadastrador)
	if(pid[10] == 0){
	
		signal(SIGUSR1, cadastrar);
		while(1) sleep(1);
	
	}
	
	else{
	pid[11] = fork();
	
	//filho 11 (autorizador de saque)
	if(pid[11] == 0){
		
		signal(SIGUSR1, autoriza_saque);
		while(1) sleep(1);
	
	}
	

	else{
	pid[12] = fork();
	
	//filho 12 (interface)
	if(pid[12] == 0){
	
	
	}

	//pai
	else{
	
		//sinal de um descritor de arquivos
		int fds;
		
		printf("pid_pai = %d\n",getpid());
		
		for(i=0; i<12; i++){
			printf("pid[%d] = %d\n",i ,pid[i]);
		
		}
		
		sleep(2);
		
		while(1){
		
			for(i=0; i<12; i++){
			
				if(i == 10){ 
					strcpy(buffer, "/tmp/cad.txt");
					
				}else if(i == 11){
					strcpy(buffer, "/tmp/saque.txt");

				}else{
					sprintf(buffer,"/tmp/pac%d.tar", i);
				}
				
				printf("%s\n", buffer);
				printf("Status fds[%d] = %d\n", i, fds = open(buffer, O_RDONLY));
				
				if(fds >= 0){ 
					
					close(fds);
					printf("autorizando filho %d [%d]\n", i, pid[i]);
					kill(pid[i], SIGUSR1);
				}
				
				close(fds);
				usleep(500000);

			
			}
				
		}
										
										
	}}}}}}}}}}}}}
	
return 0;
}

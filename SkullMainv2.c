//SkullMain v2.0
//Main User Skullpi
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <signal.h>
#include <time.h>

char user_adress[50] = " ";
char user_pass[50] = " ";
char usr = '0';

int flag_login = 0;

int fd;
FILE *fd2;


void encerrar(){
	
	puts("\nEncerrando programa...\n");
	close(fd);
	//fclose(fd2);
	exit(0);

}

int menu(){

	int user_input = 0;

	if(flag_login == 0){

		puts("\n\t\tMenu\t\t\n");
		puts("\t1 - Login\t");
		puts("\t2 - Cadastrar Diretório Skullpi\t");
		puts("\t3 - Saque\t");
		puts("\t4 - Encerrar\t\n\n");

		printf("Sua Escolha: "); 
		scanf("%d", &user_input);
	
		while(user_input < 1 || user_input > 4){
			printf("\nEntrada invalida, escolha outra: ");
			scanf("%d", &user_input);
		}

		if(user_input == 1) return 1;
		if(user_input == 2) return 2;
		if(user_input == 3) return 3;
		if(user_input == 4) return 4;

	}

	if(flag_login == 1){

		printf("\nBem vindo %s\t\t Usuário nº %c\t\n", user_adress, usr);
		puts("\n\t\tMenu\t\t\n");
		puts("\t1 - Upload\t");
		puts("\t2 - Download\t");
		puts("\t3 - Encerrar\t\n\n");

		printf("Sua Escolha: "); 
		scanf("%d", &user_input);
	
		while(user_input < 1 || user_input > 3){
			printf("\nEntrada invalida, escolha outra: ");
			scanf("%d", &user_input);		
		}

		if(user_input == 1) return 5;
		if(user_input == 2) return 6;
		if(user_input == 3) return 4;

	}

}


void cadastrar(){

	char buffer[50] = " ";
	char buffer2[50] = " ";

		printf("\n\tColoque o endereço da sua pasta de usuário /home/");
		scanf("%s",buffer);
		sprintf(user_adress,"/home/%s", buffer);
	
		printf("\tcrie uma Senha: ");
		scanf("%s",user_pass);

		system("clear");

		printf("\nUsuário: %s\n", buffer);
		printf("Senha: %s\n\n", user_pass);

		//criando e dando permissão para o arquivo de novo login (cad.txt)
		sprintf(buffer2, "echo -n %s %s > /tmp/cad.txt", buffer, user_pass);
		system(buffer2);
		system("chmod 777 /tmp/cad.txt");

		//enviando para o raspberry e removendo da maquina do usuário
		system("sshpass -p \"leonard7\" scp /tmp/cad.txt pi@192.168.42.1:/tmp");
		system("rm /tmp/cad.txt");
}

void autoriza_saque(){

	char buffer[100] = " ";
	char resposta;
	int pin=0;
	
	do{

		puts("Deseja liberar seu diretório para saque [s/n] ?");
		scanf("%c", &resposta);

	}while(resposta != 's' && resposta != 'n');

	if(resposta == 's'){

		srand(time(NULL));
		pin = rand()%10000;
						
		sprintf(buffer, "cd /tmp && echo \"%c %d\" > saque.txt",usr, pin);
		system(buffer);
		system("cd /tmp && chmod 777 saque.txt");
		system("sshpass -p \"leonard7\" scp /tmp/saque.txt pi@192.168.42.1:/tmp");
		system("rm /tmp/saque.txt");
	}
					
}

void login(){

	char buffer[50] = " ";
	char buffer2[50] = " ";
	char autenticador[100] = " ";
	char aux;
	
		printf("\n\tUsuário: ");
		scanf("%s",buffer);
		sprintf(user_adress,"/home/%s", buffer);
	
		printf("\tSua Senha: ");
		scanf("%s",user_pass);
		puts("\n");
		
		system("clear");

			//comparar arquivo cadastrados.txt (raspberry) com user_adress e user_pass

			sprintf(buffer2,"%s %s\n", buffer, user_pass);		

			system("sshpass -p \"leonard7\" scp pi@192.168.42.1:/home/pi/cadastrados.txt /tmp");

			fd2 = fopen("/tmp/cadastrados.txt", "r");
			fseek(fd2, 0, SEEK_SET);

			while((!feof(fd2)) && (flag_login == 0)){

				aux = fgetc(fd2);			
				fseek(fd2, 1, SEEK_CUR);
				fgets(autenticador, 100, fd2);

				if(strcmp(buffer2, autenticador) == 0){
					flag_login = 1;
					usr = aux;
				}
							
			}

			if(flag_login == 0){
				puts("usuario e senha incorretos ou não cadastrado!");
			
			}

			 fclose(fd2);


}
				
void upload(){

	char buffer[100];
	

	puts("iniciando upload...");
	sprintf(buffer, "cd %s && mv Skullpi usr%c", user_adress, usr);	
	system(buffer);
	sprintf(buffer, "cd %s && tar -cf pac%c.tar usr%c",user_adress,usr, usr);
	system(buffer);
	sprintf(buffer, "sshpass -p \"leonard7\" scp %s/pac%c.tar pi@192.168.42.1:/tmp", user_adress, usr);
	system(buffer);
	sprintf(buffer, "rm %s/pac%c.tar", user_adress, usr);
	system(buffer);
	sprintf(buffer, "rm -R %s/usr%c",user_adress, usr);
	printf("%s\n", buffer);	
	system(buffer);
	sprintf(buffer, "cd %s && mkdir Skullpi", user_adress);	
	printf("%s\n", buffer);
	system(buffer);
	sprintf(buffer, "chmod 777 %s/Skullpi", user_adress);
	printf("%s\n", buffer);
	system(buffer);
	puts("upload terminado...");
	sleep(1);
	system("clear");	

}

void download(){

	char buffer[100]= " ";

	
	puts("iniciando download...");
	sprintf(buffer, "sshpass -p \"leonard7\" scp pi@192.168.42.1:/tmp/pak%c.tar %s/Skullpi",usr, user_adress);	
	system(buffer);
	sprintf(buffer, "cd %s/Skullpi && tar -xvf pak%c.tar",user_adress, usr);
	system(buffer);
	sprintf(buffer, "rm %s/Skullpi/pak%c.tar", user_adress, usr);
	system(buffer);
	puts("download terminado...");
	sleep(1);
	system("clear");

}

void saque(){

	char buffer[50] = " ";
	char autenticador[100] = " ";
	int pin;

	int flag_saque = 0;

		printf("\n\tColoque o endereço da sua pasta de usuário /home/");
		scanf("%s",buffer);
		sprintf(user_adress,"/home/%s", buffer);
		
		printf("\n\tQual número do diretório gostaria de sacar:");
		scanf("%c", &usr);
		usr = getc(stdin);
	
	
		printf("\n\tPIN de acesso:");
		scanf("%d", &pin);
		puts("\n");
		
		system("clear");

			//comparar arquivo emsaque.txt (raspberry) com usr e pin

			sprintf(buffer,"%c %d\n", usr, pin);		

			system("sshpass -p \"leonard7\" scp pi@192.168.42.1:/home/pi/emsaque.txt /tmp");

			fd2 = fopen("/tmp/emsaque.txt", "r");
			fseek(fd2, 0, SEEK_SET);

			while((!feof(fd2))){

				fgets(autenticador, 100, fd2);

				if(strcmp(buffer, autenticador) == 0){
					flag_saque = 1;
				}
							
			}

			fclose(fd2);

			if(flag_saque == 0){

				puts("\n\tPin ou diretório incorretos, Saque não realizado!\t\n");
	
			}
			else{
				download();
				printf("Diretório sacado com sucesso!\n");	
				flag_saque = 0;			
			}		 
}
	


int main(){

	int flag_menu;

	signal(SIGINT, encerrar);
	system("clear");
	puts("\nBem vindo ao Skullpi!\n");

	while(1){

		flag_menu = menu();

		switch(flag_menu){

			case 1:
				
				system("clear");
				puts("Login...");
				login();

			break;

			case 2:
				
				system("clear");
     			puts("Novo cadastro...");
				cadastrar();

			break;

			case 3:
				system("clear");
				puts("Saque...");
				saque();

			break;

			case 4:

				if(flag_login == 1) autoriza_saque();

				encerrar();
				
			break;
				
			case 5:
				upload();
			
			break;

			case 6:
				download();

			break;


		}

	}


return 0;
}

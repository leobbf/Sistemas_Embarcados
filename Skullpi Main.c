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

char user_adress[50];
char user_pass[50];
char nome_pasta[50];

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

		printf("\nBem vindo %s\n", user_adress);
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


void create(){

	char buffer[50];
	char buffer2[50];

		printf("\n\tColoque o endereço da sua pasta de usuário /home/");
		scanf("%s",buffer);
		sprintf(user_adress,"/home/%s", buffer);
	
		printf("\tcrie uma Senha: ");
		scanf("%s",user_pass);

		system("clear");

		printf("\nUsuário: %s\n", buffer);
		printf("Senha: %s\n\n", user_pass);

		//criando e dando permissão para o arquivo de novo login 
		sprintf(buffer2, "echo %s %s > /tmp/login.txt", buffer, user_pass);
		system(buffer2);
		system("chmod 777 /tmp/login.txt");

		//enviando para o raspberry e removendo da maquina do usuário
		system("sshpass -p \"leonard7\" scp /tmp/login.txt pi@192.168.42.1:/tmp");
		system("rm /tmp/login.txt");

		
		/*
		//criando a pasta /home/user_adress/Skullpi
		sprintf(buffer2, "cd %s && mkdir Skullpi", user_adress);
		system(buffer2);

		//dando permissões para a pasta Skullpi
		sprintf(buffer2, "chmod 777 %s/Skullpi", user_adress);
		system(buffer2);
		*/
}

void login(){

	char buffer[50];
	char buffer2[50];
	char autenticador[100];
	
		printf("\n\tUsuário: ");
		scanf("%s",buffer);
		sprintf(nome_pasta,"%s", buffer);
		sprintf(user_adress,"/home/%s", buffer);
	
		printf("\tSua Senha: ");
		scanf("%s",user_pass);
		puts("\n");
		
		system("clear");

		//super usuário
		if(!(strcmp(buffer, "leonardo")) && !(strcmp(user_pass, "leobbf"))) flag_login = 1;

		else{

			//comparar arquivo cadastrados.txt (raspberry) com user_adress e user_pass

			sprintf(buffer2,"%s %s\n", buffer, user_pass);			

			system("sshpass -p \"leonard7\" scp pi@192.168.42.1:/home/pi/cadastrados.txt /tmp");

			fd2 = fopen("/tmp/cadastrados.txt", "r");
			fseek(fd2, 0, SEEK_SET);

			do{

				fgets(autenticador, 100, fd2);

				if(strcmp(buffer2, autenticador) == 0){
					flag_login = 1;
				}


			}while(!feof(fd2));

			if(flag_login == 0){
				puts("usuario e senha incorretos ou não cadastrado!");
			
			}

			 fclose(fd2);

		}

}


void saque(){


}

void upload(){

	char buffer[100];
	

	puts("iniciando upload...");
	sprintf(buffer, "cd %s && mv Skullpi %s", user_adress, nome_pasta);	
	system(buffer);
	sprintf(buffer, "cd %s && tar -zcf pac.tar %s",user_adress, nome_pasta);
	system(buffer);
	sprintf(buffer, "sshpass -p \"leonard7\" scp %s/pac.tar pi@192.168.42.1:/home/pi/Skullpi", user_adress);
	system(buffer);
	sprintf(buffer, "rm %s/pac.tar", user_adress);	
	system(buffer);
	sprintf(buffer, "rm -R %s/%s",user_adress, nome_pasta);	
	system(buffer);
	sprintf(buffer, "cd %s && mkdir Skullpi", user_adress);	
	system(buffer);
	sprintf(buffer, "chmod 777 %s/Skullpi", user_adress);
	system(buffer);
	puts("upload terminado...");	

}

/*void download(){

	char *buffer;

	
	puts("iniciando download...");
	sprintf(buffer, "sshpass -p \"leonard7\" scp pi@192.168.42.1:/tmp/pak.tar %s/Skullpi", user_adress);	
	system(buffer);
	sprintf(buffer, "cd %s/Skullpi && tar -zxvf pak.tar", user_adress);
	system(buffer);
	sprintf(buffer, "rm %s/Skullpi/pak.tar", user_adress);
	puts("download terminado...");

}*/


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
     			puts("Create...");
				create();

			break;

			case 3:
				system("clear");
				puts("Saque...");
				//saque();

			break;

			case 4:
				encerrar();
				
			break;
				
			case 5:
				upload();
			
			break;

			case 6:
				//download();

			break;


		}

	}


return 0;
}

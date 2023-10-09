#include<stdio.h>
#include<windows.h>
#include<string.h>

void telaMenu(){
	for(int x = 1; x <= 156; x++){
		for(int y = 1; y <= 46; y++){
			gotoxy(x, y);
			if(x == 1 || x == 156){
				printf("%c", 186);
			}
			else if(x > 1 && x < 156 && y == 1 || y == 46){
				printf("%c", 205);
			}
		}
	}
	gotoxy(1, 1);
	printf("%c", 201);
	gotoxy(156, 1);
	printf("%c", 187);
	gotoxy(1, 46);
	printf("%c", 200);
	gotoxy(156, 46);
	printf("%c", 188);
}

void telaInfo(){
	for(int x = 3; x <= 154; x++){
		for(int y = 2; y <= 8; y++){
			gotoxy(x, y);
			if(x == 3 || x == 154){
				printf("%c", 186);
			}
			else if(x > 3 && x < 154 && y == 2 || y == 8){
				printf("%c", 205);
			}
			else if( y == 4){
				printf("%c", 205);
			}
			else if(x == 81 && (y > 4 && y < 8))
				printf("%c", 186);
		}
	}
	gotoxy(3, 2);
	printf("%c", 201);
	gotoxy(154, 2);
	printf("%c", 187);
	gotoxy(3, 8);
	printf("%c", 200);
	gotoxy(154, 8);
	printf("%c", 188);
	gotoxy(3, 4);
	printf("%c", 204);
	gotoxy(154, 4);
	printf("%c", 185);
	gotoxy(81, 4);
	printf("%c", 203);
	gotoxy(81, 8);
	printf("%c", 202);
	
	gotoxy(5,3);
	printf("F1:CARREGAR SCRIPT");
	gotoxy(26,3);
	printf("F2:CARREGAR COMANDOS");
	gotoxy(49,3);
	printf("F3:VOLTAR");
	gotoxy(61,3);
	printf("F4:EXIBIR TABELAS");
}

void telaTexto(){
	for(int x = 3; x <= 154; x++){
		for(int y = 10 ; y <= 45; y++){
			gotoxy(x, y);
			if(x == 3 || x == 154){
				printf("%c", 186);
			}
			else if(x > 3 && x < 154 && y == 10 || y == 45){
				printf("%c", 205);
			}
		}
	}
	gotoxy(3, 10);
	printf("%c", 201);
	gotoxy(154, 10);
	printf("%c", 187);
	gotoxy(3, 45);
	printf("%c", 200);
	gotoxy(154, 45);
	printf("%c", 188);
}

void telaCheia() {
	keybd_event(VK_MENU  , 0x36, 0, 0);
	keybd_event(VK_RETURN, 0x1C, 0, 0);
	keybd_event(VK_RETURN, 0x1C, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_MENU  , 0x38, KEYEVENTF_KEYUP, 0);
}

void nomeBanco(char stringT[]){
	char string[50], caractere;
	int i = 0;
	
	for(int x = 60; x <= 104; x++){
		for(int y = 18; y <= 28; y++){
			gotoxy(x, y);
			if(x == 60 || x == 104){
				printf("%c", 186);
			}
			else if(x > 60 && x < 104 && y == 18 || y == 28){
				printf("%c", 205);
			}
		}
	}
	gotoxy(60, 18);
	printf("%c", 201);
	gotoxy(104, 18);
	printf("%c", 187);
	gotoxy(60, 28);
	printf("%c", 200);
	gotoxy(104, 28);
	printf("%c", 188);
	
	gotoxy(75, 20);
	printf("NOME DO ARQUIVO");
	
	for(int x = 66; x <= 98; x++){
		for(int y = 22; y <= 24; y++){
			gotoxy(x, y);
			if(x == 66 || x == 98){
				printf("%c", 179);
			}
			else if(x > 66 && x < 98 && y == 22 || y == 24){
				printf("%c", 196);
			}
		}
	}
	gotoxy(66, 22);
	printf("%c", 218);
	gotoxy(98, 22);
	printf("%c", 191);
	gotoxy(66, 24);
	printf("%c", 192);
	gotoxy(98, 24);
	printf("%c", 217);
	
	gotoxy(94, 23);
	printf(".txt");
	gotoxy(67, 23);
	caractere = getche();
	for(i = 1;caractere != 13;){
		if(caractere == 8){
			if(i > 0){
				printf(" ");
				i--;
				gotoxy(67+i, 23);
				
			}else{
				gotoxy(67, 23);
			}
		}else{
			if(i < 27){
				string[i] = caractere;
				i++;
			}
		}
		if(i < 27)
			caractere = getche();
		else{
			caractere = getch();
			gotoxy(93, 23);
		}
	}
	
	string[i] = '.';
	string[++i] = 't';
	string[++i] = 'x';
	string[++i] = 't';
	string[++i] = '\0';
	
	
	strcpy(stringT, string);
}

int main(void){
	char stringT[50];
	telaCheia();
	telaMenu();
	telaInfo();
	telaTexto();
	nomeBanco(&stringT);
	printf("%s", stringT);
	getch();
}

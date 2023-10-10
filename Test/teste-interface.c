#include<stdio.h>
#include<windows.h>
#include<conio2.h>
#include<string.h>
#include "../biblioteca/tadFilaS.h"
#include "../biblioteca/tadFilaI.h"
#include "../biblioteca/utils.h"
#include "../biblioteca/tadBanco.h"
#include "../biblioteca/tadListaColuna.h"
#include "../biblioteca/tadListaTabela.h"
#include "../biblioteca/sql.h"

void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 10;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}
void showcursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 10;
   info.bVisible = TRUE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

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
	printf("F3:EXIBIR TABELAS");
	gotoxy(69,3);
	printf("F4:SAIR");
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
	showcursor();
	gets(string);
	i = strlen(string);
	string[i] = '.';
	string[++i] = 't';
	string[++i] = 'x';
	string[++i] = 't';
	string[++i] = '\0';
		
	
	hidecursor();
	strcpy(stringT, string);	
	
}

void limpaTela(){
	for(int x = 1; x <= 153; x++){
		for(int y = 11 ; y <= 44; y++){
			gotoxy(x, y);
			if(x > 1 || x < 153){
				printf(" ");
			}
			else if(x > 1 && x < 153 && y > 11 || y < 44){
				printf(" ");
			}
		}
	}
}

void mensagemB(){
	char string[50];
	strcpy(string, "CRIANDO BANCO DE DADOS...");

	for(int i = 0; i < strlen(string); i++){
		gotoxy(5+i,6);
		Sleep(8);
		printf("%c", string[i]);
	}
	Sleep(500);
	strcpy(string, "BANCO DE DADOS CRIADO COM SUCESSO...");
	for(int i = 0; i < strlen(string); i++){
		gotoxy(5+i,6);
		Sleep(8);
		printf("%c", string[i]);
	}
	Sleep(500);
	for(int i = 0; i < strlen(string); i++){
		gotoxy(5+i,6);
		Sleep(8);
		printf(" ");
	}
}

void carregaComando(BancoDado **B){
	char caractere = 10;
	int i = 0, flag = 0;
	DescFilaString C, L;
	char string[500];
	init(&C);
	init(&L);
	showcursor();
	gotoxy(4, 11);
	printf("LINHA DE COMANDO: ");
	gotoxy(5, 13);
	gets(string);
	i++;
	while(stricmp(string, "") != 0){
		enqueue(&L, string);
		if(!filaVazia(&L)){
			criaFila(&C, &L);
			while(!filaVazia(&C)){
				topoFilaString(C, string);
				if(strcmp(string, "INSERT") == 0)
					comandoInsert(&(*B), &C);
			}
		}
		gotoxy(5, 13+i);;
		gets(string);
		i++;
	}
	hidecursor();
	for(int y = 0; y <= i ;y++){
		for(int x = 0; x < 400; x++){
			gotoxy(2+x,10+y);
			printf(" ");
		}
	}
	strcpy(string, "OPERACAO CONCLUIDA..");
	for(int i = 0; i < strlen(string); i++){
		gotoxy(5+i, 6);
		Sleep(8);
		printf("%c", string[i]);
	}
	Sleep(300);
	for(int i = 0; i < strlen(string); i++){
		gotoxy(5+i, 6);
		Sleep(8);
		printf(" ");
	}
}

void exibirBanco(BancoDado *B){
	
	PColuna *C;
	Tabela *T = B->tabela;
	Dado *D;
	int i=0;
	while(T != NULL) {
		gotoxy(5, 14+i);
		printf("NOME TABELA: %s\n", T->nome);
		C = T->coluna;
		while(C != NULL) {
			i++;
			printf("	COLUNA: %s - TIPO: %c - PK: %c - FK: ", C->campo, C->tipo, C->pk);
			if(C->fk != NULL)
				printf("%s\n", C->fk->campo);
			else
				printf("NULL\n");
			D = C->pDados;
			while(D != NULL) {
				i++;
				if(C->tipo == 'I')
				printf("	%d - %d\n", ++i, D->tipo.valorI);
				else if(C->tipo == 'T' || C->tipo == 'D')
				printf("	%d - %s\n", ++i, D->tipo.valorT);
				else if(C->tipo == 'N')
				printf("	%d - %.2lf\n", ++i, D->tipo.valorN);
				else if(C->tipo == 'C')
				printf("	%d - %c\n", ++i, D->tipo.valorC);
				D = D->prox;
			}
			C = C->prox;
		}
		i++;
		i++;
		T = T->prox;
	}
}

int main(void){
	int flag = 0;
	BancoDado *B;
	DescFilaString F;
	char stringT[50], op;
	initBancoDado(&B);
	init(&F);
	hidecursor();
	telaCheia();
	Sleep(500);
	telaInfo();
	op = getche();
	op = getche();
	while(op != 62){
		if(op == 59 && flag == 0){
			nomeBanco(stringT);
			leituraArquivo(&F, stringT);
			carregaScript(&B, &F);
			limpaTela(); 	
			mensagemB();
			flag = 1;
		}
		else if(op == 60){
			carregaComando(&B);
		}
		else if(op == 61){
			exibirBanco(B);
		}
		
		op = getche();
	}
	
}

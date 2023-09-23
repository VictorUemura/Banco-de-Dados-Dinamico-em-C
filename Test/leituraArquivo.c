#include<stdio.h>
#include<conio2.h>
#include<string.h>
#include<stdlib.h>
#include "../library/fila.h"

char verificaString(char *string, char *string2) {
	int j = 0;
	for(int i = 0; i < strlen(string) && j < strlen(string2); i++) {
		if(string[i] == string2[0]) {
				j = 0;
			while(i < strlen(string) && j < strlen(string2) && string[i] == string2[j]) {
				j++;
				i++;
			}
		}
	}
	return j == strlen(string2);
}

void indexString(char string[100], char string2[100], int *z){
	int i, j = 0;
	
	for(i = 0; i<strlen(string); i++){
		if(string[i] == string2[j]){
			*z = i;	
			j++;
		}
	}
	*z += 2;
} 

void pegaNome(char string[], int i, char nome[]){
	int j;
	for(j = 0 ; i < strlen(string) && string[i] != ';' && string[i] != ')' && string[i] != ' '; i++){
		if(string[i] != '('){
			nome[j] = string[i];
			j++;
		}
	}
	nome[j] = '\0';
}

void pegaVariavel(char string[], char nome[]){
	int i;
	
	for(i = 0; i < strlen(string) && (string[i] != ',' || string[i+1] != '\0'); i++){
		nome[i] = string[i];
	}
	nome[i] = '\0';
}

void criaListas(DescFilaString *D){
	int i;
	char string[100], nome[100], nomeV[100];
	unqueue(D, string);
	while(!filaVazia(D)){

		if(verificaString(string, "CREATE DATABASE")){
		 	indexString(string, "CREATE DATABASE", &i);
		 	pegaNome(string, i, nome);
		 	printf("%s\n", nome);
		}
	
		else if(verificaString(string, "CREATE TABLE")){
		 	indexString(string, "CREATE TABLE", &i);
		 	pegaNome(string, i, nome);
		 	printf("%s\n", nome);
		 	
			unqueue(D, string);
			while(!verificaString(string, ");")){
				pegaVariavel(string, nomeV);
				if(verificaString(string, "PRIMARY KEY")){
					indexString(string, "PRIMARY KEY", &i);
					pegaNome(string, i, nomeV);
					printf("%s\n", nomeV);
				}
				if(verificaString(string, "CHARACTER(1)")){
					pegaNome(string, 0, nomeV);
					printf("%s\n", nomeV);
				}
				if(verificaString(string, "CHARACTER(20)")){
					pegaNome(string, 0, nomeV);
					printf("%s\n", nomeV);
				}
				if(verificaString(string, "INTEGER NOT NULL;")){
					pegaNome(string, 0, nomeV);
					printf("%s\n", nomeV);
				}
				if(verificaString(string, "INTEGER")){
					pegaNome(string, 0, nomeV);
					printf("%s\n", nomeV);
				}
				if(verificaString(string, "DATE")){
					pegaNome(string, 0, nomeV);
					printf("%s\n", nomeV);
				}
				if(verificaString(string, "NUMERIC")){
					pegaNome(string, 0, nomeV);
					printf("%s\n", nomeV);
				}
				
				unqueue(D, string);
			}
		}
	
		else if(verificaString(string, "ALTER TABLE")){
			
		}
		unqueue(D, string);
	}
}

void leituraArquivo(){
	DescFilaString D;
	FILE *ptrArq = fopen("texto.txt", "r+");
	char string[100];
	
	init(&D);
	

	fscanf(ptrArq, "%[^\n]\n", &string);
	while(!feof(ptrArq)){
		enqueue(&D, string);
		fscanf(ptrArq, "%[^\n]\n", &string);
	}
	
	criaListas(&D);
	
	fclose(ptrArq);
}

int main(void){
	leituraArquivo();
	return 0;
}

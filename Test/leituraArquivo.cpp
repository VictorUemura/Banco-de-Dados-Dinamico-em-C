#include<stdio.h>
#include<conio2.h>
#include<string.h>
#include<stdlib.h>
#include "fila.h"

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

int indexString(char string[100], char string2[100]){
	int i, j = 0;
	char aux[50];
	for(i = 0; i<strlen(string); i++){
		aux[i] = string[i];
		aux[i+1] = '\0';
		if(verificaString(aux, string2))
			j++;
	}


	return j+2;
}

void pegaNome(char string[], int i, char nome[]){
	int j;
	for(j = 0 ; i < strlen(string) && string[i] != ';' && string[i] != ' ' ; i++, j++){
			nome[j] = string[i];
	}
	nome[j] = '\0';
}

void pegaVariavel(char string[], char nome[], int ativa){
	int i = 0;
	if(string[0] != ')' && string[1] != ';'){

		for(i = 0; i < strlen(string) && string[i] != ';' ; i++){
			nome[i] = string[i];
		}
		nome[i] = '\0';
	}
	else
		ativa = 0;
}

void criaListas(DescFilaString *D){
	int i, ativaT = 0;
	char string[100], nome[100], nomeV[100];
	unqueue(D, string);
	while(!filaVazia(D)){

		if(verificaString(string, "CREATE DATABASE")){
		 	i = indexString(string, "CREATE DATABASE");
		 	pegaNome(string, i, nome);
		 	printf("%s\n", nome);
		}
	
		else if(verificaString(string, "CREATE TABLE")){
		 	i = indexString(string, "CREATE TABLE");
		 	pegaNome(string, i, nome);
		 	printf("%s\n", nome);
			 ativaT = 1;
			 unqueue(D, string);
			 while(ativaT == 1){
			 	pegaVariavel(string, nomeV, ativaT);
			 	printf("%s\n", nomeV);
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

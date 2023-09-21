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


	return j;
}

/*void pegaNome(char string[100], char nome[100]){
	int i;
	char aux[50];
	for(i = 0; i < strlen(string); i++){
		
		if(string[i] == ' '){
			if(!verificaString(aux, "CREATE"))
		}
		aux[i] = string[i];
	}
}*/

void criaListas(DescFilaString *D){
	int i;
	char string[100], nome[100];
	unqueue(D, string);
	
	if(verificaString(string, "CREATE DATABASE")){
		 i = indexString(string, "CREATE DATABASE");
		 printf("%c", string[i+2]);
	}
	
	else if(verificaString(string, "CREATE TABLE")){
					
	}
	
	else if(verificaString(string, "ALTER TABLE")){
		
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

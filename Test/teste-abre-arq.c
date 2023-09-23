#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "../Library/tad.h"
#include "../Library/fila.h"
#include "../Library/leituraArquivo.h"

int main(void) {
	DescFilaString D;
	char unq[100];
	
	// Teste da fila de strings
	init(&D);
	enqueue(&D, "Elem. 1");
	enqueue(&D, "Elem. 2");
	enqueue(&D, "Elem. 3");
	enqueue(&D, "Elem. 4");
	exibeFila(D);
	unqueue(&D, unq);
	printf("Elemento removido: %s\n", unq);
	unqueue(&D, unq);
	printf("Elemento removido: %s\n", unq);
	unqueue(&D, unq);
	printf("Elemento removido: %s\n", unq);
	printf("Fila atualmente:\n");
	exibeFila(D);
	
	// Teste leitura de arquivos e criação de lista de string
	leituraArquivo();
	
	return 0;
}

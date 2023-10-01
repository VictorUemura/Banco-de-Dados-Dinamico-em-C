#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "../Library/tad.h"
#include "../Library/fila.h"
#include "../Library/leituraArquivo.h"

int main(void) {
	DescFilaString D, C;
	char unq[100];
	
	// Teste da fila de strings
	init(&D);
	
	
	// Teste leitura de arquivos e criação de lista de string
	leituraArquivo(&C, "texto.txt");
	exibeFila(C);
	
	return 0;
}

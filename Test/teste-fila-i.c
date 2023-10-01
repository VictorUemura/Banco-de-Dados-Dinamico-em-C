#include <stdio.h>
#include "../Library/filaI.h"

int main(void) {
	DescFilaI F;
	int x;
	initI(&F);
	
	// Teste de inserção
	enqueueI(&F, 10);
	enqueueI(&F, 20);
	enqueueI(&F, 30);
	
	// Teste de remoção
	unqueueI(&F, &x);
	printf("Elemento removido: %d\n", x);
	unqueueI(&F, &x);
	printf("Elemento removido: %d\n", x);
	unqueueI(&F, &x);
	printf("Elemento removido: %d\n", x);
	unqueueI(&F, &x);
	printf("Elemento removido: %d\n", x);
	
	exibeFilaI(F);
	
	return 0;
}

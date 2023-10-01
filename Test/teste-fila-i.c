#include <stdio.h>
#include "../Library/filaI.h"

int main(void) {
	DescFilaI F;
	int x;
	initI(&F);
	
	// Teste de inser��o
	enqueueI(&F, 10);
	enqueueI(&F, 20);
	enqueueI(&F, 30);
	
	// Teste de remo��o
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
